/*
Exemplo 1. Tipos de paralelismo (com threads da biblioteca padrao, std::thread).
- Paralelismo de DADOS: a mesma operacao aplicada a partes diferentes dos dados (cada thread soma
  um pedaco do vetor). Escala com o tamanho dos dados.
- Paralelismo de TAREFAS (funcional): tarefas diferentes executadas ao mesmo tempo (uma thread calcula
  a soma, outra o maximo, outra conta os pares). Limitado ao numero de tarefas distintas.
Na taxonomia de Flynn, ambos rodam numa maquina MIMD (varios fluxos de instrucoes e de dados), que e o
caso dos processadores multinucleo atuais.
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int main()
{
  const int N = 10000000;
  vector<int> v(N);
  for (int i = 0; i < N; i++) v[i] = i % 1000;

  // paralelismo de dados: P threads, cada uma com um bloco contiguo
  int P = thread::hardware_concurrency();
  if (P == 0) P = 4;
  vector<long long> parcial(P, 0);
  vector<thread> ts;
  for (int t = 0; t < P; t++)
    ts.emplace_back([&, t]() {
      int ini = (long long)N * t / P, fim = (long long)N * (t + 1) / P;   // divide [0, N) em P blocos
      long long s = 0;
      for (int i = ini; i < fim; i++) s += v[i];
      parcial[t] = s;   // cada thread escreve na sua posicao: sem conflito
    });
  for (thread &t : ts) t.join();   // espera todas terminarem
  long long soma = 0;
  for (long long s : parcial) soma += s;
  cout << "Dados: " << P << " threads somaram " << soma << endl;

  // paralelismo de tarefas: tres tarefas diferentes sobre o mesmo vetor
  long long total = 0;
  int maior = 0, pares = 0;
  thread a([&]() { for (int x : v) total += x; });
  thread b([&]() { for (int x : v) if (x > maior) maior = x; });
  thread c([&]() { for (int x : v) if (x % 2 == 0) pares++; });
  a.join(); b.join(); c.join();
  cout << "Tarefas: soma = " << total << ", maior = " << maior << ", pares = " << pares << endl;
  return 0;
}
