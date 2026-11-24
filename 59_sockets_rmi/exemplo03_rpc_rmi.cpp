/*
Exemplo 3. Invocacao remota de metodos (RMI no Java; RPC em geral): o cliente chama um metodo de um objeto que
esta em OUTRO processo/maquina como se fosse local. A estrutura e sempre:
  - interface: os metodos que o objeto remoto oferece (aqui a classe abstrata Calculadora);
  - stub (proxy, lado cliente): implementa a interface; cada chamada vira uma mensagem
    (empacotamento ou "marshalling" do nome do metodo e dos parametros) enviada pela rede;
  - skeleton (lado servidor): recebe a mensagem, desempacota, chama o objeto real e devolve o resultado;
  - registro (rmiregistry / servico de nomes): associa um nome ("calculadora") ao endereco do objeto.
Protocolo de texto: "metodo arg1 arg2" -> "OK resultado" ou "ERRO mensagem".
Compilar: g++ -std=c++17 -pthread arquivo.cpp   (Windows: acrescente -lws2_32)
*/
#include <iostream>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <map>
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

const int PORTA_REGISTRO = 5003, PORTA_OBJETO = 5004;

class Calculadora {   // interface remota
public:
  virtual double soma(double a, double b) = 0;
  virtual double divide(double a, double b) = 0;
  virtual ~Calculadora() {}
};

class CalculadoraReal : public Calculadora {   // implementacao, so existe no servidor
public:
  double soma(double a, double b) override { return a + b; }
  double divide(double a, double b) override { if (b == 0) throw runtime_error("divisao por zero"); return a / b; }
};

// skeleton: traduz mensagens em chamadas ao objeto real
void skeleton(Socket escuta, Calculadora &obj, int conexoes)
{
  for (int c = 0; c < conexoes; c++) {
    Socket con = accept(escuta, nullptr, nullptr);
    string pedido;
    while (recebeLinha(con, pedido)) {
      stringstream ss(pedido);
      string metodo; double a, b;
      ss >> metodo >> a >> b;   // desempacota
      try {
        double r;
        if (metodo == "soma") r = obj.soma(a, b);
        else if (metodo == "divide") r = obj.divide(a, b);
        else throw runtime_error("metodo inexistente");
        enviaLinha(con, "OK " + to_string(r));
      } catch (exception &e) { enviaLinha(con, string("ERRO ") + e.what()); }   // excecao remota volta como mensagem
    }
    fechaSocket(con);
  }
}

// servico de nomes: "lookup nome" -> porta do objeto
void registro(Socket escuta, map<string, int> nomes, int consultas)
{
  for (int c = 0; c < consultas; c++) {
    Socket con = accept(escuta, nullptr, nullptr);
    string pedido;
    recebeLinha(con, pedido);
    string nome = pedido.substr(pedido.find(' ') + 1);
    enviaLinha(con, nomes.count(nome) ? to_string(nomes[nome]) : "-1");
    fechaSocket(con);
  }
}

// stub: para o cliente, parece uma Calculadora comum
class CalculadoraStub : public Calculadora {
  Socket s;
  double chama(const string &metodo, double a, double b)
  {
    enviaLinha(s, metodo + " " + to_string(a) + " " + to_string(b));   // empacota e envia
    string resp;
    recebeLinha(s, resp);
    if (resp.rfind("OK ", 0) == 0) return stod(resp.substr(3));
    throw runtime_error("remota: " + resp.substr(5));
  }
public:
  CalculadoraStub(int porta) : s(conectaTCP(porta)) {}
  ~CalculadoraStub() { fechaSocket(s); }
  double soma(double a, double b) override { return chama("soma", a, b); }
  double divide(double a, double b) override { return chama("divide", a, b); }
};

int lookup(const string &nome)   // pergunta ao registro onde esta o objeto
{
  Socket s = conectaTCP(PORTA_REGISTRO);
  enviaLinha(s, "lookup " + nome);
  string porta;
  recebeLinha(s, porta);
  fechaSocket(s);
  return stoi(porta);
}

int main()
{
  CalculadoraReal real;
  Socket escReg = criaServidorTCP(PORTA_REGISTRO), escObj = criaServidorTCP(PORTA_OBJETO);
  thread tReg(registro, escReg, map<string, int>{{"calculadora", PORTA_OBJETO}}, 1);
  thread tObj(skeleton, escObj, ref(real), 1);

  {
    int porta = lookup("calculadora");
    cout << "Registro: \"calculadora\" esta na porta " << porta << endl;
    CalculadoraStub stub(porta);
    Calculadora &calc = stub;   // daqui em diante o codigo nao sabe que o objeto e remoto
    cout << "soma(2.5, 4) = " << calc.soma(2.5, 4) << endl;
    cout << "divide(10, 4) = " << calc.divide(10, 4) << endl;
    try { calc.divide(1, 0); }
    catch (exception &e) { cout << "Excecao: " << e.what() << endl; }
  }   // destrutor do stub fecha a conexao
  tReg.join(); tObj.join();
  fechaSocket(escReg); fechaSocket(escObj);
  return 0;
}
