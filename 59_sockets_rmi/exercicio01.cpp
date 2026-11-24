/*
Exercicio 1. Servidor TCP concorrente: para atender varios clientes ao mesmo tempo, o servidor cria uma thread
por conexao aceita (senao um cliente lento bloquearia todos). Os clientes enviam comandos "inc k" e "valor" para
um contador compartilhado no servidor, protegido por mutex. Rodar 5 clientes em paralelo, cada um somando 1..100,
e conferir o valor final (5 * 5050).
Compilar: g++ -std=c++17 -pthread arquivo.cpp   (Windows: acrescente -lws2_32)
*/
#include <iostream>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <mutex>
#include <sstream>
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

const int PORTA = 5005, CLIENTES = 5;
long long contador = 0;
mutex mtx;

void atende(Socket con)   // uma thread destas por cliente
{
  string cmd;
  while (recebeLinha(con, cmd)) {
    stringstream ss(cmd);
    string op; long long k = 0;
    ss >> op >> k;
    lock_guard<mutex> t(mtx);
    if (op == "inc") contador += k;
    enviaLinha(con, to_string(contador));
  }
  fechaSocket(con);
}

void servidor(Socket escuta)
{
  vector<thread> ts;
  for (int c = 0; c < CLIENTES; c++) {
    Socket con = accept(escuta, nullptr, nullptr);
    ts.emplace_back(atende, con);   // volta logo para o accept
  }
  for (thread &t : ts) t.join();
}

void cliente(int id)
{
  Socket s = conectaTCP(PORTA);
  string r;
  for (int i = 1; i <= 100; i++) { enviaLinha(s, "inc " + to_string(i)); recebeLinha(s, r); }
  enviaLinha(s, "valor");
  recebeLinha(s, r);
  { lock_guard<mutex> t(mtx); cout << "cliente " << id << " terminou; contador no servidor = " << r << endl; }
  fechaSocket(s);
}

int main()
{
  Socket escuta = criaServidorTCP(PORTA);
  thread srv(servidor, escuta);
  vector<thread> cs;
  for (int i = 0; i < CLIENTES; i++) cs.emplace_back(cliente, i);
  for (thread &t : cs) t.join();
  srv.join();
  fechaSocket(escuta);
  cout << "Valor final: " << contador << " (esperado " << CLIENTES * 5050 << ")" << endl;
  return 0;
}
