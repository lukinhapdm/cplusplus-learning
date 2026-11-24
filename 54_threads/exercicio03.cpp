/*
Exercicio 3. Pool de threads: um numero fixo de threads trabalhadoras retira tarefas de uma fila compartilhada,
evitando o custo de criar uma thread por tarefa. Implementar a classe PoolThreads com submete(tarefa) e
o destrutor que espera a fila esvaziar. Usar o pool para calcular a soma dos divisores de 1..20000,
uma tarefa por bloco de 500 numeros.
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <atomic>
using namespace std;

class PoolThreads {
  vector<thread> trabalhadoras;
  queue<function<void()>> tarefas;
  mutex mtx;
  condition_variable cv;
  bool encerrando = false;

  void laco()
  {
    while (true) {
      function<void()> tarefa;
      {
        unique_lock<mutex> trava(mtx);
        cv.wait(trava, [this]() { return encerrando || !tarefas.empty(); });
        if (encerrando && tarefas.empty()) return;   // nada mais a fazer
        tarefa = tarefas.front(); tarefas.pop();
      }
      tarefa();   // executa fora da secao critica
    }
  }

public:
  PoolThreads(int n) { for (int i = 0; i < n; i++) trabalhadoras.emplace_back(&PoolThreads::laco, this); }

  void submete(function<void()> f)
  {
    { lock_guard<mutex> trava(mtx); tarefas.push(f); }
    cv.notify_one();
  }

  ~PoolThreads()
  {
    { lock_guard<mutex> trava(mtx); encerrando = true; }
    cv.notify_all();
    for (thread &t : trabalhadoras) t.join();
  }
};

long long somaDivisores(int x) { long long s = 0; for (int d = 1; d <= x; d++) if (x % d == 0) s += d; return s; }

int main()
{
  const int N = 20000;
  atomic<long long> total(0);
  atomic<int> tarefasFeitas(0);
  {
    PoolThreads pool(4);
    for (int ini = 1; ini <= N; ini += 500)
      pool.submete([ini, &total, &tarefasFeitas]() {
        long long s = 0;
        for (int x = ini; x < ini + 500 && x <= N; x++) s += somaDivisores(x);
        total += s;
        tarefasFeitas++;
      });
  }   // destrutor: espera todas as tarefas
  long long seq = 0;
  for (int x = 1; x <= N; x++) seq += somaDivisores(x);
  cout << tarefasFeitas << " tarefas executadas por 4 threads; soma = " << total << " (sequencial: " << seq << ")" << endl;
  return 0;
}
