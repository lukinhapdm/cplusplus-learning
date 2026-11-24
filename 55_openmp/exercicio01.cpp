/*
Exercicio 1. Calcular pi pela integracao numerica de 4 / (1 + x^2) entre 0 e 1 (regra do ponto medio com
N retangulos) em paralelo com OpenMP, de tres formas:
  (a) reduction (correto e rapido);
  (b) vetor de somas parciais, uma posicao por thread (correto, mas sofre "false sharing": as posicoes
      vizinhas ficam na mesma linha de cache e as threads ficam invalidando a cache umas das outras);
      a correcao e espacar as posicoes (8 doubles = 64 bytes, o tamanho tipico de uma linha de cache;
      o tamanho da diferenca depende da maquina e do numero de nucleos);
  (c) critical a cada iteracao (correto, porem lentissimo: serializa tudo).
Compilar: g++ -std=c++17 -O2 -fopenmp arquivo.cpp
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <omp.h>
using namespace std;

const long long N = 100000000;

int main()
{
  double passo = 1.0 / N, ini, soma;

  ini = omp_get_wtime(); soma = 0;
  #pragma omp parallel for reduction(+:soma)
  for (long long i = 0; i < N; i++) { double x = (i + 0.5) * passo; soma += 4.0 / (1 + x * x); }
  printf("reduction:      pi = %.12f  (%.3f s)\n", soma * passo, omp_get_wtime() - ini);

  for (int espaco : {1, 8}) {
    ini = omp_get_wtime();
    volatile double parcial[64 * 8] = {0};   // volatile: obriga cada += a ir a memoria (senao o compilador usa registrador)
    #pragma omp parallel
    {
      int id = omp_get_thread_num(), p = omp_get_num_threads();
      for (long long i = id; i < N; i += p) { double x = (i + 0.5) * passo; parcial[id * espaco] += 4.0 / (1 + x * x); }
    }
    soma = 0;
    for (int t = 0; t < 64; t++) soma += parcial[t * espaco];
    printf("vetor parcial, espaco %d: pi = %.12f  (%.3f s)\n", espaco, soma * passo, omp_get_wtime() - ini);
  }

  ini = omp_get_wtime(); soma = 0;
  const long long M = N / 100;   // 100 vezes menos iteracoes, senao demora demais
  #pragma omp parallel for
  for (long long i = 0; i < M; i++) {
    double x = (i + 0.5) / M;
    #pragma omp critical
    soma += 4.0 / (1 + x * x);
  }
  printf("critical (N/100): pi = %.12f  (%.3f s)\n", soma / M, omp_get_wtime() - ini);
  printf("valor real:     pi = %.12f\n", acos(-1.0));
  return 0;
}
