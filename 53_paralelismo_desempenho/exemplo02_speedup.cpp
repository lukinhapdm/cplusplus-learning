/*
Exemplo 2. Desempenho de programas paralelos.
- Speedup S(p) = T(1) / T(p): quantas vezes mais rapido com p processadores (ideal: S = p).
- Eficiencia E(p) = S(p) / p: fracao do tempo em que os processadores trabalham de fato (ideal: 1).
- Lei de Amdahl: se uma fracao f do programa e sequencial, S(p) <= 1 / (f + (1 - f) / p),
  e nunca passa de 1 / f, por mais processadores que se use.
Mede o tempo de contar primos ate N com 1, 2, 4, ... threads (o numero real de nucleos limita o ganho).
Compilar: g++ -std=c++17 -O2 -pthread arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdio>
using namespace std;

bool primo(int x)
{
  if (x < 2) return false;
  for (int d = 2; d * d <= x; d++) if (x % d == 0) return false;
  return true;
}

// divisao ciclica por blocos de 1000 (bloco b vai para a thread b % p): espalha os numeros grandes,
// que custam mais, entre todas as threads
long long contaPrimos(int N, int p)
{
  vector<long long> parcial(p, 0);
  vector<thread> ts;
  for (int t = 0; t < p; t++)
    ts.emplace_back([&, t]() {
      for (int b = t * 1000; b <= N; b += p * 1000)
        for (int x = b; x < b + 1000 && x <= N; x++) if (primo(x)) parcial[t]++;
    });
  for (thread &t : ts) t.join();
  long long total = 0;
  for (long long c : parcial) total += c;
  return total;
}

int main()
{
  const int N = 3000000;
  unsigned nucleos = thread::hardware_concurrency();
  cout << "Nucleos disponiveis: " << nucleos << endl;
  printf("threads   primos     tempo(s)  speedup  eficiencia\n");
  double t1 = 0;
  for (int p = 1; p <= 8; p *= 2) {
    auto ini = chrono::steady_clock::now();
    long long c = contaPrimos(N, p);
    double t = chrono::duration<double>(chrono::steady_clock::now() - ini).count();
    if (p == 1) t1 = t;
    printf("%5d  %9lld  %10.3f  %7.2f  %9.2f\n", p, c, t, t1 / t, t1 / t / p);
  }
  return 0;
}
