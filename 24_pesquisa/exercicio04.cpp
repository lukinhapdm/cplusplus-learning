/*
Exercicio 4. Comparar na pratica a pesquisa sequencial e a binaria: para vetores ordenados de tamanho
10, 100, 1000 e 10000, procurar todas as chaves existentes e mostrar a media de comparacoes de cada metodo.
*/
#include <iostream>
#include <cmath>
using namespace std;

int sequencial(int v[], int n, int chave, long &comp)
{
  for (int i = 0; i < n; i++) { comp++; if (v[i] == chave) return i; }
  return -1;
}

int binaria(int v[], int n, int chave, long &comp)
{
  int esq = 0, dir = n - 1;
  while (esq <= dir) {
    int meio = (esq + dir) / 2;
    comp++;
    if (v[meio] == chave) return meio;
    if (chave < v[meio]) dir = meio - 1; else esq = meio + 1;
  }
  return -1;
}

int main()
{
  int tamanhos[] = {10, 100, 1000, 10000};
  for (int n : tamanhos) {
    int *v = new int[n];
    for (int i = 0; i < n; i++) v[i] = 2 * i;   // vetor ordenado de pares
    long cs = 0, cb = 0;
    for (int i = 0; i < n; i++) { sequencial(v, n, v[i], cs); binaria(v, n, v[i], cb); }
    cout << "n = " << n << "\tsequencial: " << (double)cs / n
         << "\tbinaria: " << (double)cb / n << "\t(log2 n = " << log2(n) << ")" << endl;
    delete[] v;
  }
  return 0;
}
