/*
7.1.4 Exercício 7. Função (vetor, tam, A, B) que retorna true se todos em [A,B]; testar no main.
*/
#include <iostream>
using namespace std;

// se algum elemento estiver fora de [a, b], ja retorna falso
bool noIntervalo(int v[], int n, int a, int b)
{
  for (int i = 0; i < n; i++)
    if (v[i] < a || v[i] > b) return false;
  return true;
}

int main()
{
  int v[5] = {3, 7, 4, 9, 5};
  cout << noIntervalo(v, 5, 1, 10) << endl;   // 1 (verdadeiro)
  cout << noIntervalo(v, 5, 4, 10) << endl;   // 0 (falso: 3 esta fora)
  return 0;
}
