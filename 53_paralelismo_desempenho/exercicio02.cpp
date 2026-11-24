/*
Exercicio 2. Balanceamento de carga: contar primos ate N com 4 threads usando tres divisoes do trabalho:
  (a) blocos contiguos: a ultima thread fica com os numeros maiores (mais caros) -> desequilibrio;
  (b) ciclica: x = t, t + p, t + 2p, ... (armadilha: com p par, as threads pares so recebem numeros
      pares, que sao descartados na hora, e todo o trabalho cai nas threads impares);
  (c) dinamica: um contador atomico compartilhado entrega pedacos de 1000 numeros a quem estiver livre.
Medir o tempo de cada thread e o tempo total (o total e o da thread mais lenta).
Compilar: g++ -std=c++17 -O2 -pthread arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstdio>
using namespace std;

bool primo(int x)
{
  if (x < 2) return false;
  for (int d = 2; d * d <= x; d++) if (x % d == 0) return false;
  return true;
}

const int N = 4000000, P = 4;

void executa(const char *nome, int modo)
{
  vector<long long> cont(P, 0);
  vector<double> tempo(P);
  atomic<int> proximo(0);
  auto ini = chrono::steady_clock::now();
  vector<thread> ts;
  for (int t = 0; t < P; t++)
    ts.emplace_back([&, t]() {
      auto i0 = chrono::steady_clock::now();
      if (modo == 0) { for (int x = (long long)N * t / P; x < (long long)N * (t + 1) / P; x++) cont[t] += primo(x); }
      else if (modo == 1) { for (int x = t; x < N; x += P) cont[t] += primo(x); }
      else {
        int bloco;
        while ((bloco = proximo.fetch_add(1000)) < N)   // pega o proximo pedaco livre
          for (int x = bloco; x < bloco + 1000 && x < N; x++) cont[t] += primo(x);
      }
      tempo[t] = chrono::duration<double>(chrono::steady_clock::now() - i0).count();
    });
  for (thread &t : ts) t.join();
  double total = chrono::duration<double>(chrono::steady_clock::now() - ini).count();
  long long primos = 0;
  for (long long c : cont) primos += c;
  printf("%-10s primos = %lld, total %.3f s, por thread:", nome, primos, total);
  for (double x : tempo) printf(" %.3f", x);
  printf("\n");
}

int main()
{
  executa("blocos", 0);
  executa("ciclica", 1);
  executa("dinamica", 2);
  return 0;
}
