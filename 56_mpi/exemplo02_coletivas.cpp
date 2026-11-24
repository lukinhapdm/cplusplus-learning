/*
Exemplo 2. Comunicacao coletiva em MPI: todos os processos do comunicador participam da chamada.
  - MPI_Bcast: a raiz envia o mesmo dado para todos;
  - MPI_Scatter: a raiz divide um vetor em pedacos iguais, um para cada processo;
  - MPI_Gather: o inverso, a raiz junta os pedacos de todos;
  - MPI_Reduce: combina (soma, maximo...) os valores de todos na raiz; MPI_Allreduce entrega a todos;
  - MPI_Barrier: ninguem passa ate todos chegarem.
Sao mais simples e normalmente mais eficientes (comunicacao em arvore) que varios Send/Recv.
Exemplo: media e desvio padrao de um vetor distribuido entre os processos.
Compilar: mpic++ -std=c++17 arquivo.cpp -o programa      Executar: mpirun -np 4 ./programa
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

  int porProcesso = 0;
  vector<double> dados;
  if (rank == 0) {   // so a raiz tem o vetor inteiro
    porProcesso = 5;
    dados.resize(porProcesso * size);
    for (size_t i = 0; i < dados.size(); i++) dados[i] = (i * 37) % 11;
  }
  MPI_Bcast(&porProcesso, 1, MPI_INT, 0, MPI_COMM_WORLD);   // todos ficam sabendo o tamanho do pedaco

  vector<double> pedaco(porProcesso);
  MPI_Scatter(dados.data(), porProcesso, MPI_DOUBLE, pedaco.data(), porProcesso, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  double somaLocal = 0;
  for (double x : pedaco) somaLocal += x;
  double somaTotal;
  MPI_Allreduce(&somaLocal, &somaTotal, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);   // todos recebem a soma
  double media = somaTotal / (porProcesso * size);

  double quadLocal = 0, quadTotal = 0;
  for (double x : pedaco) quadLocal += (x - media) * (x - media);
  MPI_Reduce(&quadLocal, &quadTotal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);   // so a raiz recebe

  vector<double> mediasLocais(size);
  double mediaLocal = somaLocal / porProcesso;
  MPI_Gather(&mediaLocal, 1, MPI_DOUBLE, mediasLocais.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    cout << "Media local de cada processo:";
    for (double m : mediasLocais) cout << " " << m;
    cout << "\nMedia geral = " << media << ", desvio padrao = " << sqrt(quadTotal / dados.size()) << endl;
  }
  MPI_Finalize();
  return 0;
}
