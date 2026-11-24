/*
Exemplo 2. Condicao de corrida (race condition): duas threads alteram a mesma variavel sem sincronizacao.
"contador++" nao e uma operacao unica: le, soma 1 e escreve. Se duas threads leem o mesmo valor antes de
escrever, um incremento se perde. O trecho que acessa o dado compartilhado e a SECAO CRITICA.
Solucoes:
  - mutex (exclusao mutua): so uma thread por vez dentro da secao critica (lock_guard trava e destrava
    sozinho, mesmo se houver excecao);
  - atomic: operacoes indivisiveis feitas pelo hardware, mais leves para variaveis simples.
Compilar: g++ -std=c++17 -O2 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>
using namespace std;

const int THREADS = 4, VEZES = 1000000;

volatile long long semProtecao = 0;   // volatile so impede o compilador de juntar os incrementos
long long comMutex = 0;
atomic<long long> atomico(0);
mutex mtx;

template <typename F>
double roda(F f)
{
  auto ini = chrono::steady_clock::now();
  vector<thread> ts;
  for (int t = 0; t < THREADS; t++) ts.emplace_back(f);
  for (thread &t : ts) t.join();
  return chrono::duration<double>(chrono::steady_clock::now() - ini).count();
}

int main()
{
  double t1 = roda([]() { for (int i = 0; i < VEZES; i++) semProtecao = semProtecao + 1; });
  double t2 = roda([]() { for (int i = 0; i < VEZES; i++) { lock_guard<mutex> trava(mtx); comMutex++; } });
  double t3 = roda([]() { for (int i = 0; i < VEZES; i++) atomico++; });
  cout << "Esperado:     " << (long long)THREADS * VEZES << endl;
  cout << "Sem protecao: " << semProtecao << " (" << t1 << " s)  <- incrementos perdidos" << endl;
  cout << "Com mutex:    " << comMutex << " (" << t2 << " s)" << endl;
  cout << "Atomico:      " << atomico << " (" << t3 << " s)" << endl;
  return 0;
}
