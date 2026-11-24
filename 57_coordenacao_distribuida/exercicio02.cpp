/*
Exercicio 2. Eleicao em anel (Chang e Roberts) com threads: os processos formam um anel logico e so falam com
o sucessor. Os ids sao distintos e embaralhados ao redor do anel.
  - cada processo envia o proprio id ao sucessor;
  - ao receber um id: se for maior que o seu, repassa; se for menor, descarta (o seu ja circula);
  - se receber o PROPRIO id, ele deu a volta: e o maior, vira lider e envia ELEITO, que circula o anel uma vez.
Contar as mensagens (entre n e n^2 de candidatura, conforme a ordem dos ids, mais n de anuncio).
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <vector>
#include <atomic>
using namespace std;

struct Mensagem { bool eleito; int id; };

struct Caixa {
  deque<Mensagem> fila;
  mutex mtx;
  condition_variable cv;
  void envia(Mensagem m) { { lock_guard<mutex> t(mtx); fila.push_back(m); } cv.notify_one(); }
  Mensagem recebe() { unique_lock<mutex> t(mtx); cv.wait(t, [this]() { return !fila.empty(); }); Mensagem m = fila.front(); fila.pop_front(); return m; }
};

const int N = 8;
int ids[N] = {17, 4, 29, 11, 8, 35, 2, 20};   // id do processo na posicao i do anel
Caixa caixa[N];
atomic<int> mensagens(0);
int liderVisto[N];

void processo(int pos)
{
  int meu = ids[pos], prox = (pos + 1) % N;
  auto manda = [&](Mensagem m) { mensagens++; caixa[prox].envia(m); };
  manda({false, meu});   // candidata-se
  while (true) {
    Mensagem m = caixa[pos].recebe();
    if (m.eleito) {
      liderVisto[pos] = m.id;
      if (m.id != meu) manda(m);   // repassa o anuncio; o lider para quando ele volta
      break;
    }
    if (m.id > meu) manda(m);                  // candidato mais forte: repassa
    else if (m.id == meu) manda({true, meu});  // deu a volta: sou o lider
    // m.id < meu: descarta
  }
}

int main()
{
  vector<thread> ts;
  for (int i = 0; i < N; i++) ts.emplace_back(processo, i);
  for (thread &t : ts) t.join();
  cout << "Lider visto por cada processo:";
  for (int i = 0; i < N; i++) cout << " " << liderVisto[i];
  cout << "\nMensagens: " << mensagens << " (n = " << N << ", n^2 = " << N * N << ")" << endl;
  return 0;
}
