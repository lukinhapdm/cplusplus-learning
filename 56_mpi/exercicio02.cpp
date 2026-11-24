/*
Exercicio 2. Multiplicacao matriz x vetor (y = A x) com MPI, dividindo A por blocos de linhas:
  1) a raiz cria A (N x N) e x; MPI_Bcast envia x inteiro para todos;
  2) MPI_Scatter manda N/size linhas de A para cada processo;
  3) cada processo calcula seu pedaco de y; MPI_Gather junta y na raiz, que confere com a versao sequencial.
N precisa ser multiplo do numero de processos (para simplificar).
Compilar: mpic++ -std=c++17 -O2 arquivo.cpp -o programa      Executar: mpirun -np 4 ./programa
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const int N = 8 * 120;   // divisivel por 1, 2, 3, 4, 5, 6, 8...
  if (N % size != 0) {
    if (rank == 0) cout << "N = " << N << " nao e divisivel por " << size << " processos" << endl;
    MPI_Finalize();
    return 0;
  }
  int linhas = N / size;
  vector<double> A, x(N), y;
  if (rank == 0) {
    A.resize((size_t)N * N);   // matriz guardada linha a linha num vetor (contigua, como o MPI precisa)
    for (int i = 0; i < N; i++) {
      x[i] = i % 7;
      for (int j = 0; j < N; j++) A[(size_t)i * N + j] = (i + 2 * j) % 5;
    }
    y.resize(N);
  }
  MPI_Bcast(x.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  vector<double> blocoA((size_t)linhas * N), blocoY(linhas, 0);
  MPI_Scatter(A.data(), linhas * N, MPI_DOUBLE, blocoA.data(), linhas * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  for (int i = 0; i < linhas; i++)
    for (int j = 0; j < N; j++) blocoY[i] += blocoA[(size_t)i * N + j] * x[j];

  MPI_Gather(blocoY.data(), linhas, MPI_DOUBLE, y.data(), linhas, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    double erro = 0;
    for (int i = 0; i < N; i++) {
      double s = 0;
      for (int j = 0; j < N; j++) s += A[(size_t)i * N + j] * x[j];
      erro = max(erro, fabs(s - y[i]));
    }
    cout << size << " processos, " << linhas << " linhas cada: y[0] = " << y[0] << ", y[N-1] = " << y[N - 1]
         << ", diferenca maxima para o sequencial = " << erro << endl;
  }
  MPI_Finalize();
  return 0;
}
