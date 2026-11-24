/*
Exercicio 1. Arvore de recursao: para T(n) = a T(n/b) + n^k, o nivel i tem a^i nos, cada um com custo
(n / b^i)^k. Imprimir, nivel a nivel, quantidade de nos, custo de cada no e custo total do nivel, e a soma
de todos os niveis, para tres recorrencias que caem nos tres casos do Teorema Mestre:
  T(n) = 4T(n/2) + n    (custo cresce para as folhas)
  T(n) = 2T(n/2) + n    (custo igual em todos os niveis)
  T(n) = 2T(n/2) + n^2  (custo diminui a partir da raiz)
*/
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

void arvore(int a, int b, int k, double n)
{
  printf("T(n) = %dT(n/%d) + n^%d, n = %.0f\n", a, b, k, n);
  printf("  nivel   nos        custo/no      custo do nivel\n");
  double total = 0, nos = 1, tam = n;
  for (int i = 0; tam >= 1; i++) {
    double custoNo = pow(tam, k), nivel = nos * custoNo;
    printf("  %3d  %8.0f  %14.0f  %16.0f\n", i, nos, custoNo, nivel);
    total += nivel;
    nos *= a; tam /= b;
  }
  printf("  total = %.0f\n\n", total);
}

int main()
{
  arvore(4, 2, 1, 64);
  arvore(2, 2, 1, 64);
  arvore(2, 2, 2, 64);
  return 0;
}
