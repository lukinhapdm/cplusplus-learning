/*
Exercicio 1. Contar quantas comparacoes e trocas o Bubble Sort faz para ordenar um vetor lido do usuario.
*/
#include <iostream>
using namespace std;

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }
void troca(int &a, int &b) { int t = a; a = b; b = t; }

int main()
{
  int n; cout << "N: "; cin >> n;
  int *v = new int[n];
  for (int i = 0; i < n; i++) cin >> v[i];
  long comp = 0, trocas = 0;
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++) {
      comp++;   // toda comparacao conta
      if (v[j] > v[j + 1]) { troca(v[j], v[j + 1]); trocas++; }
    }
  imprime(v, n);
  cout << "Comparacoes: " << comp << " | Trocas: " << trocas << endl;
  delete[] v;
  return 0;
}
