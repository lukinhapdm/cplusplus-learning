/*
Exercicio 3. Objeto remoto com estado: uma ContaBancaria fica no servidor e varios clientes usam stubs para
chamar deposita, saca e saldo ao mesmo tempo. O servidor atende cada cliente numa thread e o objeto real
protege seu estado com mutex (as chamadas remotas chegam concorrentemente). Saque sem saldo vira excecao remota.
3 clientes fazem 50 depositos de 10 e 50 saques de 5; o saldo final deve ser 100 + 3 * 250 = 850.
Compilar: g++ -std=c++17 -pthread arquivo.cpp   (Windows: acrescente -lws2_32)
*/
#include <iostream>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <mutex>
#include <stdexcept>
using namespace std;

// ---------- camada minima de sockets, igual no Linux, macOS e Windows ----------
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET Socket;
void fechaSocket(Socket s) { closesocket(s); }
struct IniciaRede { IniciaRede() { WSADATA w; WSAStartup(MAKEWORD(2, 2), &w); } ~IniciaRede() { WSACleanup(); } } iniciaRede;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int Socket;
void fechaSocket(Socket s) { close(s); }
#endif

sockaddr_in endereco(int porta)   // 127.0.0.1:porta (localhost)
{
  sockaddr_in e{};
  e.sin_family = AF_INET;
  e.sin_port = htons(porta);                  // ordem de bytes da rede (big-endian)
  e.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  return e;
}

Socket criaServidorTCP(int porta)   // socket -> bind -> listen
{
  Socket s = socket(AF_INET, SOCK_STREAM, 0);
  int sim = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *)&sim, sizeof(sim));   // reaproveita a porta logo
  sockaddr_in e = endereco(porta);
  if (bind(s, (sockaddr *)&e, sizeof(e)) < 0) { perror("bind"); exit(1); }
  listen(s, 10);   // fila de ate 10 conexoes esperando accept
  return s;
}

Socket conectaTCP(int porta)   // socket -> connect
{
  Socket s = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in e = endereco(porta);
  if (connect(s, (sockaddr *)&e, sizeof(e)) < 0) { perror("connect"); exit(1); }
  return s;
}

void enviaLinha(Socket s, const string &linha)   // TCP e um fluxo de bytes: "\n" marca o fim de cada mensagem
{
  string m = linha + "\n";
  size_t enviado = 0;
  while (enviado < m.size()) {
    int n = send(s, m.data() + enviado, m.size() - enviado, 0);   // send pode enviar so uma parte
    if (n <= 0) return;
    enviado += n;
  }
}

bool recebeLinha(Socket s, string &linha)   // false quando a conexao foi fechada
{
  linha.clear();
  char c;
  while (true) {
    int n = recv(s, &c, 1, 0);
    if (n <= 0) return !linha.empty();
    if (c == '\n') return true;
    linha += c;
  }
}
// -------------------------------------------------------------------------------

const int PORTA = 5007, CLIENTES = 3;

class Conta {   // interface remota
public:
  virtual void deposita(long long v) = 0;
  virtual void saca(long long v) = 0;
  virtual long long saldo() = 0;
  virtual ~Conta() {}
};

class ContaReal : public Conta {
  long long s = 100;
  mutex mtx;
public:
  void deposita(long long v) override { lock_guard<mutex> t(mtx); s += v; }
  void saca(long long v) override { lock_guard<mutex> t(mtx); if (v > s) throw runtime_error("saldo insuficiente"); s -= v; }
  long long saldo() override { lock_guard<mutex> t(mtx); return s; }
};

void skeleton(Socket con, Conta &conta)
{
  string pedido;
  while (recebeLinha(con, pedido)) {
    stringstream ss(pedido);
    string metodo; long long v = 0;
    ss >> metodo >> v;
    try {
      if (metodo == "deposita") { conta.deposita(v); enviaLinha(con, "OK"); }
      else if (metodo == "saca") { conta.saca(v); enviaLinha(con, "OK"); }
      else if (metodo == "saldo") enviaLinha(con, "OK " + to_string(conta.saldo()));
      else enviaLinha(con, "ERRO metodo inexistente");
    } catch (exception &e) { enviaLinha(con, string("ERRO ") + e.what()); }
  }
  fechaSocket(con);
}

class ContaStub : public Conta {
  Socket s;
  string chama(const string &msg)
  {
    enviaLinha(s, msg);
    string r;
    recebeLinha(s, r);
    if (r.rfind("ERRO", 0) == 0) throw runtime_error("remota: " + r.substr(5));
    return r.size() > 3 ? r.substr(3) : "";
  }
public:
  ContaStub() : s(conectaTCP(PORTA)) {}
  ~ContaStub() { fechaSocket(s); }
  void deposita(long long v) override { chama("deposita " + to_string(v)); }
  void saca(long long v) override { chama("saca " + to_string(v)); }
  long long saldo() override { return stoll(chama("saldo")); }
};

int main()
{
  ContaReal conta;
  Socket escuta = criaServidorTCP(PORTA);
  thread srv([&]() {
    vector<thread> ts;
    for (int c = 0; c < CLIENTES + 1; c++) ts.emplace_back(skeleton, accept(escuta, nullptr, nullptr), ref(conta));
    for (thread &t : ts) t.join();
  });

  vector<thread> cs;
  for (int c = 0; c < CLIENTES; c++)
    cs.emplace_back([]() {
      ContaStub stub;
      for (int i = 0; i < 50; i++) { stub.deposita(10); stub.saca(5); }
    });
  for (thread &t : cs) t.join();

  {
    ContaStub stub;   // mais um cliente: consulta e tenta um saque grande demais
    cout << "Saldo final: " << stub.saldo() << " (esperado " << 100 + CLIENTES * 250 << ")" << endl;
    try { stub.saca(1000000); }
    catch (exception &e) { cout << "Excecao: " << e.what() << endl; }
  }
  srv.join();
  fechaSocket(escuta);
  return 0;
}
