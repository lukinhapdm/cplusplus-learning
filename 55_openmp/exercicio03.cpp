/*
Exercicio 3. Histograma em paralelo: contar quantos valores caem em cada uma de 10 faixas.
  (a) atomic em cada incremento do vetor compartilhado;
  (b) histograma privado por thread, somado no final dentro de um critical (uma vez por thread);
  (c) reduction de vetor (OpenMP 4.5+): reduction(+:hist[:FAIXAS]).
Conferir que os tres batem com a versao sequencial e comparar os tempos.
Compilar: g++ -std=c++17 -O2 -fopenmp arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
using namespace std;

const int FAIXAS = 10;

int main()
{
  const int N = 30000000;
  vector<int> v(N);
  srand(3);
  for (int &x : v) x = rand() % 1000;

  long long seq[FAIXAS] = {0};
  for (int x : v) seq[x / 100]++;

  long long a[FAIXAS] = {0}, b[FAIXAS] = {0}, c[FAIXAS] = {0};
  double ini = omp_get_wtime();
  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    #pragma omp atomic
    a[v[i] / 100]++;
  }
  double tA = omp_get_wtime() - ini;

  ini = omp_get_wtime();
  #pragma omp parallel
  {
    long long local[FAIXAS] = {0};   // privado de cada thread
    #pragma omp for nowait
    for (int i = 0; i < N; i++) local[v[i] / 100]++;
    #pragma omp critical
    for (int f = 0; f < FAIXAS; f++) b[f] += local[f];
  }
  double tB = omp_get_wtime() - ini;

  ini = omp_get_wtime();
  #pragma omp parallel for reduction(+:c[:FAIXAS])
  for (int i = 0; i < N; i++) c[v[i] / 100]++;
  double tC = omp_get_wtime() - ini;

  bool ok = true;
  for (int f = 0; f < FAIXAS; f++) ok = ok && a[f] == seq[f] && b[f] == seq[f] && c[f] == seq[f];
  for (int f = 0; f < FAIXAS; f++) printf("[%3d, %3d): %lld\n", f * 100, f * 100 + 100, seq[f]);
  printf("atomic %.3f s | privado + critical %.3f s | reduction de vetor %.3f s | %s\n", tA, tB, tC,
         ok ? "todos corretos" : "ERRO");
  return 0;
}
