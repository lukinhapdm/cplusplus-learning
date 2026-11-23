/*
Exercicio 1. Funcao template que ordena um vetor de qualquer tipo (Insertion Sort) e funcao template para imprimir.
*/
#include <iostream>
#include <string>
using namespace std;

template <typename T>
void ordena(T v[], int n)
{
  for (int i = 1; i < n; i++) {
    T x = v[i]; int j = i - 1;
    while (j >= 0 && v[j] > x) { v[j + 1] = v[j]; j--; }
    v[j + 1] = x;
  }
}

template <typename T>
void imprime(T v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }

int main()
{
  int a[] = {5, 1, 4};
  double b[] = {2.2, 0.5, 1.1};
  string c[] = {"pera", "uva", "banana"};
  ordena(a, 3); imprime(a, 3);
  ordena(b, 3); imprime(b, 3);
  ordena(c, 3); imprime(c, 3);
  return 0;
}
