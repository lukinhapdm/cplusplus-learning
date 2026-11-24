/*
Exercicio 1. Calcular pi pela integral de 4 / (1 + x^2) em [0, 1] com MPI: cada processo soma os retangulos
i = rank, rank + size, rank + 2 size, ... e MPI_Reduce junta as somas no processo 0. Medir o tempo com MPI_Wtime.
Compilar: mpic++ -std=c++17 -O2 arquivo.cpp -o programa      Executar: mpirun -np 4 ./programa
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long long N = 100000000;
  MPI_Barrier(MPI_COMM_WORLD);   // todos comecam juntos para medir o tempo
  double ini = MPI_Wtime();
  double passo = 1.0 / N, local = 0;
  for (long long i = rank; i < N; i += size) {
    double x = (i + 0.5) * passo;
    local += 4.0 / (1 + x * x);
  }
  local *= passo;
  double pi;
  MPI_Reduce(&local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  double tempo = MPI_Wtime() - ini;

  if (rank == 0) printf("%d processos: pi = %.12f (erro %.2e) em %.3f s\n", size, pi, fabs(pi - acos(-1.0)), tempo);
  MPI_Finalize();
  return 0;
}
