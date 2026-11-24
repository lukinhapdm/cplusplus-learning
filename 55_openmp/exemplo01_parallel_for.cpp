/*
Exemplo 1. OpenMP: paralelismo de memoria compartilhada por diretivas (#pragma omp ...) que o compilador
transforma em threads. Modelo fork-join: a thread mestre cria uma equipe na regiao paralela e espera
todas no final dela.
  - #pragma omp parallel                -> a regiao e executada por todas as threads da equipe;
  - #pragma omp parallel for            -> divide as iteracoes do laco entre as threads;
  - reduction(+:soma)                   -> cada thread soma numa copia privada; no fim as copias sao somadas;
  - private / shared                    -> variavel propria de cada thread / compartilhada (padrao).
  - omp_get_thread_num(), omp_get_num_threads(), omp_get_wtime() (relogio em segundos).
Compilar: g++ -std=c++17 -O2 -fopenmp arquivo.cpp   (o numero de threads pode ser definido por OMP_NUM_THREADS)
*/
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main()
{
  #pragma omp parallel
  {
    int id = omp_get_thread_num();   // declarada dentro da regiao: privada
    #pragma omp critical
    cout << "Ola da thread " << id << " de " << omp_get_num_threads() << endl;
  }

  const int N = 50000000;
  vector<double> v(N);
  #pragma omp parallel for
  for (int i = 0; i < N; i++) v[i] = 1.0 / (i + 1);   // iteracoes independentes

  for (int p : {1, 2, 4}) {
    double soma = 0, ini = omp_get_wtime();
    #pragma omp parallel for reduction(+:soma) num_threads(p)
    for (int i = 0; i < N; i++) soma += v[i];
    cout << p << " thread(s): soma harmonica = " << soma << " em " << omp_get_wtime() - ini << " s" << endl;
  }

  double errada = 0;   // sem reduction: condicao de corrida na variavel compartilhada
  #pragma omp parallel for
  for (int i = 0; i < 1000000; i++) errada += 1;
  cout << "Sem reduction: " << errada << " (esperado 1000000; pode dar menos)" << endl;
  return 0;
}
