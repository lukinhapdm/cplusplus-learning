/*
Exemplo 2. Sockets UDP: sem conexao. Cada sendto envia um DATAGRAMA independente para (IP, porta), e cada
recvfrom recebe um datagrama inteiro e informa quem enviou. Nao ha garantia de entrega nem de ordem, mas o
custo e menor (sem estabelecer conexao): usado em DNS, jogos, streaming. Aqui um servidor de horario/consulta:
o cliente manda o nome de uma cidade e recebe a temperatura (valores ficticios).
Compilar: g++ -std=c++17 -pthread arquivo.cpp   (Windows: acrescente -lws2_32)
*/
#include <iostream>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <map>
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

const int PORTA = 5002;

void servidor(Socket s, int pedidos)
{
  map<string, string> temperatura = {{"recife", "31 C"}, {"curitiba", "14 C"}, {"manaus", "33 C"}};
  char buf[512];
  for (int i = 0; i < pedidos; i++) {
    sockaddr_in quem{};
    socklen_t tam = sizeof(quem);
    int n = recvfrom(s, buf, sizeof(buf) - 1, 0, (sockaddr *)&quem, &tam);   // recebe e descobre o remetente
    if (n <= 0) continue;
    buf[n] = 0;
    string cidade = buf;
    string r = temperatura.count(cidade) ? cidade + ": " + temperatura[cidade] : cidade + ": desconhecida";
    sendto(s, r.data(), r.size(), 0, (sockaddr *)&quem, tam);                 // responde para quem enviou
  }
}

int main()
{
  Socket srv = socket(AF_INET, SOCK_DGRAM, 0);   // SOCK_DGRAM = UDP
  sockaddr_in e = endereco(PORTA);
  if (bind(srv, (sockaddr *)&e, sizeof(e)) < 0) { perror("bind"); return 1; }
  thread t(servidor, srv, 3);

  Socket cli = socket(AF_INET, SOCK_DGRAM, 0);   // o cliente nem precisa de bind: o sistema escolhe a porta
  for (string cidade : {"recife", "curitiba", "lisboa"}) {
    sendto(cli, cidade.data(), cidade.size(), 0, (sockaddr *)&e, sizeof(e));
    char buf[512];
    int n = recvfrom(cli, buf, sizeof(buf) - 1, 0, nullptr, nullptr);
    buf[n > 0 ? n : 0] = 0;
    cout << "Datagrama recebido: " << buf << endl;
  }
  t.join();
  fechaSocket(cli); fechaSocket(srv);
  return 0;
}
