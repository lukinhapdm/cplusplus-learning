/*
Exercicio 1. Problema da subsequencia (subvetor) de soma maxima, resolvido em tres ordens de complexidade:
  (a) O(n^3): testa todo par (i, j) e soma de i a j;
  (b) O(n^2): para cada i, acumula a soma enquanto j avanca;
  (c) O(n):   algoritmo de Kadane (a melhor soma terminando em j estende a de j-1 ou recomeca).
Contar as operacoes de soma para n = 100, 200 e 400 e observar: dobrar n multiplica o custo por 8, 4 e 2.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

long long ops;

int cubico(int v[], int n)
{
  int melhor = 0;
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++) {
      int s = 0;
      for (int k = i; k <= j; k++) { s += v[k]; ops++; }
      if (s > melhor) melhor = s;
    }
  return melhor;
}

int quadratico(int v[], int n)
{
  int melhor = 0;
  for (int i = 0; i < n; i++) {
    int s = 0;
    for (int j = i; j < n; j++) { s += v[j]; ops++; if (s > melhor) melhor = s; }
  }
  return melhor;
}

int linear(int v[], int n)
{
  int melhor = 0, atual = 0;
  for (int j = 0; j < n; j++) {
    atual += v[j]; ops++;
    if (atual < 0) atual = 0;   // soma negativa nao ajuda: recomeca
    if (atual > melhor) melhor = atual;
  }
  return melhor;
}

int main()
{
  srand(3);
  long long anterior[3] = {0, 0, 0};
  for (int n : {100, 200, 400}) {
    int *v = new int[n];
    for (int i = 0; i < n; i++) v[i] = rand() % 21 - 10;
    int (*alg[3])(int[], int) = {cubico, quadratico, linear};
    const char *nome[3] = {"O(n^3)", "O(n^2)", "O(n)  "};
    cout << "n = " << n << endl;
    for (int a = 0; a < 3; a++) {
      ops = 0;
      int r = alg[a](v, n);
      cout << "  " << nome[a] << ": soma maxima " << r << ", " << ops << " operacoes";
      if (anterior[a]) cout << " (x" << (double)ops / anterior[a] << ")";
      cout << endl;
      anterior[a] = ops;
    }
    delete[] v;
  }
  return 0;
}
