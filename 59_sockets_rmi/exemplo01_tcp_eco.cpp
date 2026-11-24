/*
Exemplo 1. Sockets TCP: um socket e uma ponta de comunicacao identificada por (endereco IP, porta).
TCP oferece uma conexao confiavel e ordenada (fluxo de bytes), estabelecida antes da troca de dados.
  Servidor: socket -> bind (associa a porta) -> listen (aceita pedidos) -> accept (espera um cliente) -> recv/send
  Cliente:  socket -> connect (ao endereco do servidor) -> send/recv -> close
Aqui o servidor de "eco" devolve cada linha em maiusculas. Para o exemplo rodar sozinho, o servidor roda numa
thread do mesmo programa; com os argumentos "servidor" ou "cliente" cada parte roda em um terminal separado.
Compilar: g++ -std=c++17 -pthread arquivo.cpp   (Windows: acrescente -lws2_32)
*/
#include <iostream>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cctype>
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

const int PORTA = 5001;

void servidor(Socket escuta, int clientes)
{
  for (int c = 0; c < clientes; c++) {
    Socket con = accept(escuta, nullptr, nullptr);   // bloqueia ate um cliente conectar
    string linha;
    while (recebeLinha(con, linha)) {
      for (char &ch : linha) ch = toupper((unsigned char)ch);
      enviaLinha(con, "ECO: " + linha);
    }
    fechaSocket(con);   // cliente fechou: atende o proximo
  }
}

void cliente()
{
  Socket s = conectaTCP(PORTA);
  for (string msg : {"ola servidor", "sockets tcp", "tchau"}) {
    enviaLinha(s, msg);
    string resposta;
    recebeLinha(s, resposta);
    cout << "enviou \"" << msg << "\", recebeu \"" << resposta << "\"" << endl;
  }
  fechaSocket(s);
}

int main(int argc, char *argv[])
{
  string modo = argc > 1 ? argv[1] : "ambos";
  if (modo == "servidor") { cout << "Servidor na porta " << PORTA << endl; servidor(criaServidorTCP(PORTA), 1000000); }
  else if (modo == "cliente") cliente();
  else {
    Socket escuta = criaServidorTCP(PORTA);   // ja escutando antes de o cliente tentar conectar
    thread t(servidor, escuta, 1);
    cliente();
    t.join();
    fechaSocket(escuta);
  }
  return 0;
}
