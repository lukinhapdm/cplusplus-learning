/*
Exercicio 2. Protocolo de aplicacao sobre TCP: um mini servidor HTTP. O cliente envia
  "GET /caminho HTTP/1.0" + cabecalhos + linha em branco
e o servidor responde "HTTP/1.0 200 OK" (ou 404) + cabecalhos (Content-Length) + linha em branco + corpo.
Rotas: /ola, /soma?a=X&b=Y. Depois de rodar, tambem da para abrir http://localhost:5006/ola no navegador
executando o programa com o argumento "servidor".
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

const int PORTA = 5006;

map<string, string> parametros(const string &consulta)   // "a=2&b=3" -> {a:2, b:3}
{
  map<string, string> p;
  size_t i = 0;
  while (i < consulta.size()) {
    size_t e = consulta.find('&', i);
    if (e == string::npos) e = consulta.size();
    string par = consulta.substr(i, e - i);
    size_t igual = par.find('=');
    if (igual != string::npos) p[par.substr(0, igual)] = par.substr(igual + 1);
    i = e + 1;
  }
  return p;
}

void atende(Socket con)
{
  string linha, pedido;
  recebeLinha(con, pedido);                                     // "GET /soma?a=2&b=3 HTTP/1.0\r"
  while (recebeLinha(con, linha) && linha != "\r" && !linha.empty()) {}   // ignora os cabecalhos
  string caminho = pedido.substr(4, pedido.find(' ', 4) - 4), consulta;
  if (caminho.find('?') != string::npos) { consulta = caminho.substr(caminho.find('?') + 1); caminho = caminho.substr(0, caminho.find('?')); }

  string status = "200 OK", corpo;
  if (caminho == "/ola") corpo = "Ola do servidor HTTP em C++!";
  else if (caminho == "/soma") {
    auto p = parametros(consulta);
    corpo = to_string(atoi(p["a"].c_str()) + atoi(p["b"].c_str()));
  } else { status = "404 Not Found"; corpo = "Pagina nao encontrada"; }
  string resposta = "HTTP/1.0 " + status + "\r\nContent-Type: text/plain\r\nContent-Length: " +
                    to_string(corpo.size()) + "\r\n\r\n" + corpo;
  send(con, resposta.data(), resposta.size(), 0);
  fechaSocket(con);   // HTTP/1.0: uma requisicao por conexao
}

string requisita(const string &caminho)
{
  Socket s = conectaTCP(PORTA);
  string req = "GET " + caminho + " HTTP/1.0\r\nHost: localhost\r\n\r\n";
  send(s, req.data(), req.size(), 0);
  string resposta, linha;
  while (recebeLinha(s, linha)) resposta += linha + "\n";   // le ate o servidor fechar
  fechaSocket(s);
  return resposta;
}

int main(int argc, char *argv[])
{
  Socket escuta = criaServidorTCP(PORTA);
  if (argc > 1 && string(argv[1]) == "servidor") {
    cout << "Abra http://localhost:" << PORTA << "/ola no navegador (Ctrl+C encerra)" << endl;
    while (true) atende(accept(escuta, nullptr, nullptr));
  }
  thread srv([escuta]() { for (int i = 0; i < 3; i++) atende(accept(escuta, nullptr, nullptr)); });
  for (string c : {"/ola", "/soma?a=20&b=22", "/nada"}) cout << ">>> GET " << c << "\n" << requisita(c) << endl;
  srv.join();
  fechaSocket(escuta);
  return 0;
}
