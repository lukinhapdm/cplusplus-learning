/*
Exemplo 1. MPI (Message Passing Interface): paralelismo de memoria DISTRIBUIDA. Varios processos (podem
estar em maquinas diferentes) executam o MESMO programa, cada um com sua memoria; trocam dados so por mensagens.
  - MPI_Init / MPI_Finalize: inicia e encerra o ambiente;
  - MPI_Comm_size: quantos processos;  MPI_Comm_rank: numero (rank) deste processo, de 0 a size-1;
  - MPI_Send(buf, qtd, tipo, destino, tag, comunicador) e MPI_Recv(buf, qtd, tipo, origem, tag, com, status):
    comunicacao ponto a ponto; a tag identifica o tipo de mensagem; MPI_ANY_SOURCE aceita qualquer origem.
O comportamento de cada processo e escolhido pelo rank (modelo SPMD: um programa, varios dados).
Compilar: mpic++ -std=c++17 arquivo.cpp -o programa      Executar: mpirun -np 4 ./programa
(Windows com MS-MPI no MSYS2: g++ -std=c++17 arquivo.cpp -o programa -lmsmpi e mpiexec -n 4 programa.exe)
*/
#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // 1) todos mandam uma saudacao para o processo 0, que imprime na ordem em que chegarem
  if (rank != 0) {
    int dado = rank * rank;
    MPI_Send(&dado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else {
    cout << "Processo 0 de " << size << " recebendo:" << endl;
    for (int i = 1; i < size; i++) {
      int dado;
      MPI_Status st;
      MPI_Recv(&dado, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &st);
      cout << "  " << dado << " do processo " << st.MPI_SOURCE << endl;
    }
  }

  // 2) anel: um "token" passa por 0 -> 1 -> ... -> size-1 -> 0, e cada um soma seu rank
  if (size > 1) {
    int token;
    if (rank == 0) {
      token = 0;
      MPI_Send(&token, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
      MPI_Recv(&token, 1, MPI_INT, size - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cout << "Token voltou ao 0 valendo " << token << " (soma dos ranks = " << size * (size - 1) / 2 << ")" << endl;
    } else {
      MPI_Recv(&token, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      token += rank;
      MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}
