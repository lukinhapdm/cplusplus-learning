/*
Exercicio 3. Ordenacao paralela odd-even (transposicao par-impar) com MPI:
  1) cada processo recebe n/p numeros (Scatter) e ordena localmente;
  2) p fases: na fase par, os pares de processos (0,1), (2,3)... trocam seus blocos; na fase impar, (1,2), (3,4)...;
     em cada par, o processo da esquerda fica com os n/p MENORES e o da direita com os MAIORES
     (MPI_Sendrecv troca os dados sem risco de deadlock);
  3) apos p fases tudo esta ordenado; Gather junta na raiz.
Compilar: mpic++ -std=c++17 -O2 arquivo.cpp -o programa      Executar: mpirun -np 4 ./programa
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const int local = 6;   // numeros por processo
  vector<int> todos, meu(local), vizinho(local), junto(2 * local);
  if (rank == 0) {
    todos.resize(local * size);
    srand(7);
    for (int &x : todos) x = rand() % 100;
    cout << "Entrada:";
    for (int x : todos) cout << " " << x;
    cout << endl;
  }
  MPI_Scatter(todos.data(), local, MPI_INT, meu.data(), local, MPI_INT, 0, MPI_COMM_WORLD);
  sort(meu.begin(), meu.end());

  for (int fase = 0; fase < size; fase++) {
    int parceiro;
    if (fase % 2 == 0) parceiro = rank % 2 == 0 ? rank + 1 : rank - 1;   // pares (0,1), (2,3)...
    else parceiro = rank % 2 == 0 ? rank - 1 : rank + 1;                 // pares (1,2), (3,4)...
    if (parceiro < 0 || parceiro >= size) continue;                       // sem par nesta fase
    MPI_Sendrecv(meu.data(), local, MPI_INT, parceiro, fase, vizinho.data(), local, MPI_INT, parceiro, fase,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    merge(meu.begin(), meu.end(), vizinho.begin(), vizinho.end(), junto.begin());
    if (rank < parceiro) copy(junto.begin(), junto.begin() + local, meu.begin());   // fica com os menores
    else copy(junto.begin() + local, junto.end(), meu.begin());                     // fica com os maiores
  }

  MPI_Gather(meu.data(), local, MPI_INT, todos.data(), local, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    cout << "Saida:  ";
    for (int x : todos) cout << " " << x;
    cout << (is_sorted(todos.begin(), todos.end()) ? "  (ordenado)" : "  (ERRO)") << endl;
  }
  MPI_Finalize();
  return 0;
}
