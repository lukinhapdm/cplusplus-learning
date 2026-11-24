/*
Exercicio 1. Multiplicacao de matrizes N x N em paralelo: cada thread calcula um bloco de linhas de C = A x B
(as linhas sao independentes, nao ha secao critica). Conferir com a versao sequencial e medir o speedup
para 1, 2 e 4 threads.
Compilar: g++ -std=c++17 -O2 -pthread arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;

typedef vector<vector<double>> Matriz;
const int N = 400;

void multiplicaLinhas(const Matriz &A, const Matriz &B, Matriz &C, int ini, int fim)
{
  for (int i = ini; i < fim; i++)
    for (int k = 0; k < N; k++) {   // ordem i-k-j aproveita melhor a cache
      double a = A[i][k];
      for (int j = 0; j < N; j++) C[i][j] += a * B[k][j];
    }
}

double paralelo(const Matriz &A, const Matriz &B, Matriz &C, int p)
{
  for (auto &l : C) fill(l.begin(), l.end(), 0.0);
  auto ini = chrono::steady_clock::now();
  vector<thread> ts;
  for (int t = 0; t < p; t++) ts.emplace_back(multiplicaLinhas, cref(A), cref(B), ref(C), N * t / p, N * (t + 1) / p);
  for (thread &t : ts) t.join();
  return chrono::duration<double>(chrono::steady_clock::now() - ini).count();
}

int main()
{
  srand(1);
  Matriz A(N, vector<double>(N)), B = A, C = A, ref1 = A;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) { A[i][j] = rand() % 10; B[i][j] = rand() % 10; }

  double t1 = paralelo(A, B, ref1, 1);
  for (int p : {1, 2, 4}) {
    double t = paralelo(A, B, C, p);
    cout << p << " thread(s): " << t << " s, speedup " << t1 / t << ", resultado " << (C == ref1 ? "igual" : "DIFERENTE") << endl;
  }
  return 0;
}
