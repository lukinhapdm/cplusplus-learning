/*
Exercicio 2. Paralelismo recursivo com tarefas OpenMP (#pragma omp task): mergesort em que as duas metades
viram tarefas independentes; taskwait espera as duas antes de intercalar. Abaixo de um limite (corte),
ordena sequencialmente, para nao criar tarefas pequenas demais.
Uma unica thread (single) dispara a recursao; as outras da equipe executam as tarefas criadas.
Compilar: g++ -std=c++17 -O2 -fopenmp arquivo.cpp
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <omp.h>
using namespace std;

const int CORTE = 10000;

void mergesort(vector<int> &v, vector<int> &aux, int ini, int fim)   // [ini, fim)
{
  if (fim - ini <= CORTE) { sort(v.begin() + ini, v.begin() + fim); return; }
  int meio = (ini + fim) / 2;
  #pragma omp task shared(v, aux)
  mergesort(v, aux, ini, meio);
  #pragma omp task shared(v, aux)
  mergesort(v, aux, meio, fim);
  #pragma omp taskwait
  merge(v.begin() + ini, v.begin() + meio, v.begin() + meio, v.begin() + fim, aux.begin() + ini);
  copy(aux.begin() + ini, aux.begin() + fim, v.begin() + ini);
}

int main()
{
  const int N = 10000000;
  vector<int> v(N), aux(N);
  srand(5);
  for (int &x : v) x = rand();
  vector<int> copia = v;

  double ini = omp_get_wtime();
  sort(copia.begin(), copia.end());
  double tSeq = omp_get_wtime() - ini;

  ini = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    mergesort(v, aux, 0, N);
  }
  double tPar = omp_get_wtime() - ini;
  cout << "std::sort sequencial: " << tSeq << " s" << endl;
  cout << "mergesort com tasks:  " << tPar << " s com " << omp_get_max_threads() << " threads" << endl;
  cout << "Resultado " << (v == copia ? "correto" : "INCORRETO") << endl;
  return 0;
}
