/*
Exercicio 3. Granularidade e sobrecarga: criar uma thread custa caro. Somar 1..N de tres formas:
  (a) sequencial;
  (b) 4 threads, cada uma com um quarto do trabalho (granularidade grossa);
  (c) uma thread nova para cada pedaco de 1000 numeros (granularidade fina demais).
Mostrar que, com tarefas muito pequenas, o custo de criar e sincronizar threads supera o ganho.
Compilar: g++ -std=c++17 -O2 -pthread arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdio>
using namespace std;

const long long N = 20000000;

long long somaIntervalo(long long a, long long b)   // soma com um pouco de trabalho por elemento
{
  long long s = 0;
  for (long long i = a; i < b; i++) s += i % 7;
  return s;
}

double mede(long long (*f)(), long long &resultado)
{
  auto ini = chrono::steady_clock::now();
  resultado = f();
  return chrono::duration<double>(chrono::steady_clock::now() - ini).count();
}

long long sequencial() { return somaIntervalo(0, N); }

long long grossa()
{
  vector<long long> p(4);
  vector<thread> ts;
  for (int t = 0; t < 4; t++) ts.emplace_back([&, t]() { p[t] = somaIntervalo(N * t / 4, N * (t + 1) / 4); });
  for (thread &t : ts) t.join();
  return p[0] + p[1] + p[2] + p[3];
}

long long fina()   // uma thread por pedaco de 1000: 20 mil threads criadas e destruidas
{
  long long total = 0;
  for (long long ini = 0; ini < N; ini += 1000) {
    long long s = 0;
    thread t([&]() { s = somaIntervalo(ini, min(ini + 1000, N)); });
    t.join();
    total += s;
  }
  return total;
}

int main()
{
  long long r;
  printf("sequencial: %.3f s", mede(sequencial, r)); printf(" (soma %lld)\n", r);
  printf("grossa:     %.3f s", mede(grossa, r));     printf(" (soma %lld)\n", r);
  printf("fina:       %.3f s", mede(fina, r));       printf(" (soma %lld)\n", r);
  return 0;
}
