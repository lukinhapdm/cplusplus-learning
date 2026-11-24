/*
Exemplo 2. Exclusao mutua distribuida - algoritmo de Ricart e Agrawala. Nao ha coordenador nem memoria
compartilhada: cada processo (aqui, uma thread com sua propria caixa de mensagens) so troca mensagens.
Para entrar na secao critica (SC), o processo envia PEDIDO(relogio de Lamport, id) a todos e espera N - 1 OKs.
Ao receber um PEDIDO, responde OK na hora se nao quer a SC ou se o pedido do outro e mais antigo
(menor (relogio, id)); senao adia o OK ate sair da SC. Custo: 2(N - 1) mensagens por entrada.
Um contador atomico confere que nunca ha dois processos na SC ao mesmo tempo.
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <vector>
#include <atomic>
#include <chrono>
using namespace std;

const int N = 4, VEZES = 3;
enum Tipo { PEDIDO, OK, FIM };
struct Mensagem { Tipo tipo; int relogio, de; };

struct Caixa {   // canal de mensagens de um processo
  deque<Mensagem> fila;
  mutex mtx;
  condition_variable cv;
  void envia(Mensagem m) { { lock_guard<mutex> t(mtx); fila.push_back(m); } cv.notify_one(); }
  Mensagem recebe()
  {
    unique_lock<mutex> t(mtx);
    cv.wait(t, [this]() { return !fila.empty(); });
    Mensagem m = fila.front(); fila.pop_front();
    return m;
  }
};

Caixa caixa[N];
atomic<int> naSC(0), totalSC(0), mensagens(0), violacoes(0);
mutex saida;

void processo(int id)
{
  int relogio = 0, meuPedido = 0, oks = 0, feitas = 0;
  bool querendo = false;
  vector<bool> adiado(N, false);
  auto manda = [&](int para, Tipo t) { mensagens++; caixa[para].envia({t, relogio, id}); };

  while (true) {
    if (!querendo && feitas < VEZES) {   // decide pedir a SC
      querendo = true; meuPedido = ++relogio; oks = 0;
      for (int j = 0; j < N; j++) if (j != id) manda(j, PEDIDO);
    }
    if (querendo && oks == N - 1) {      // recebeu todos os OKs: entra
      if (++naSC > 1) violacoes++;
      { lock_guard<mutex> s(saida); cout << "P" << id << " na secao critica (pedido com relogio " << meuPedido << ")" << endl; }
      this_thread::sleep_for(chrono::milliseconds(2));
      naSC--;
      querendo = false; feitas++;
      for (int j = 0; j < N; j++) if (adiado[j]) { manda(j, OK); adiado[j] = false; }   // libera quem esperava
      if (++totalSC == N * VEZES) for (int j = 0; j < N; j++) caixa[j].envia({FIM, 0, id});
      continue;
    }
    Mensagem m = caixa[id].recebe();
    if (m.tipo == FIM) break;
    relogio = max(relogio, m.relogio) + 1;
    if (m.tipo == OK) oks++;
    else {   // PEDIDO: o mais antigo tem prioridade; empate decidido pelo id
      bool outroPrimeiro = m.relogio < meuPedido || (m.relogio == meuPedido && m.de < id);
      if (!querendo || outroPrimeiro) manda(m.de, OK);
      else adiado[m.de] = true;
    }
  }
}

int main()
{
  vector<thread> ts;
  for (int i = 0; i < N; i++) ts.emplace_back(processo, i);
  for (thread &t : ts) t.join();
  cout << totalSC << " entradas na SC, " << violacoes << " violacoes de exclusao mutua, " << mensagens
       << " mensagens (2(N-1) por entrada = " << 2 * (N - 1) * N * VEZES << ")" << endl;
  return 0;
}
