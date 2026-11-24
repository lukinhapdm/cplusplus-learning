/*
Exemplo 2. Escalonamento de lacos e sincronizacao em OpenMP.
schedule(...) define como as iteracoes sao distribuidas:
  - static: blocos fixos definidos antes de comecar (baixo custo; ruim se as iteracoes tem custos diferentes);
  - dynamic, k: cada thread pega k iteracoes por vez quando fica livre (equilibra, com algum custo);
  - guided: pedacos que comecam grandes e vao diminuindo.
Sincronizacao: critical (um por vez num bloco), atomic (uma operacao simples indivisivel),
barrier (todas esperam ate todas chegarem), single (so uma thread executa o bloco).
sections: tarefas diferentes, uma em cada thread (paralelismo de tarefas).
Compilar: g++ -std=c++17 -O2 -fopenmp arquivo.cpp
*/
#include <iostream>
#include <cmath>
#include <omp.h>
using namespace std;

double trabalho(int i)   // custo cresce com i: iteracoes desbalanceadas
{
  double s = 0;
  for (int k = 0; k < i; k++) s += sin(k) * cos(k);
  return s;
}

int main()
{
  const int N = 20000;
  double s, ini;

  ini = omp_get_wtime(); s = 0;
  #pragma omp parallel for schedule(static) reduction(+:s)
  for (int i = 0; i < N; i++) s += trabalho(i);
  cout << "static:      " << omp_get_wtime() - ini << " s" << endl;

  ini = omp_get_wtime(); s = 0;
  #pragma omp parallel for schedule(dynamic, 100) reduction(+:s)
  for (int i = 0; i < N; i++) s += trabalho(i);
  cout << "dynamic,100: " << omp_get_wtime() - ini << " s" << endl;

  ini = omp_get_wtime(); s = 0;
  #pragma omp parallel for schedule(guided) reduction(+:s)
  for (int i = 0; i < N; i++) s += trabalho(i);
  cout << "guided:      " << omp_get_wtime() - ini << " s" << endl;

  int contAtomico = 0, maiorCritical = 0, maiorReduction = 0;
  #pragma omp parallel for reduction(max:maiorReduction)
  for (int i = 0; i < 100000; i++) {
    int x = (int)((i * 7919LL) % 100003);
    #pragma omp atomic
    contAtomico++;
    #pragma omp critical
    if (x > maiorCritical) maiorCritical = x;   // le e escreve: precisa ser tudo junto, por isso critical
    if (x > maiorReduction) maiorReduction = x; // alternativa melhor: reduction(max:...)
  }
  cout << "atomic: " << contAtomico << ", maximo com critical: " << maiorCritical
       << ", com reduction(max): " << maiorReduction << endl;

  #pragma omp parallel
  {
    #pragma omp single
    cout << "single: so uma das " << omp_get_num_threads() << " threads imprime isto" << endl;
    // ha uma barreira implicita no fim do single
    #pragma omp sections
    {
      #pragma omp section
      { double r = trabalho(5000);
        #pragma omp critical
        cout << "  secao A pela thread " << omp_get_thread_num() << " (" << r << ")" << endl; }
      #pragma omp section
      { double r = trabalho(6000);
        #pragma omp critical
        cout << "  secao B pela thread " << omp_get_thread_num() << " (" << r << ")" << endl; }
    }
  }
  return 0;
}
