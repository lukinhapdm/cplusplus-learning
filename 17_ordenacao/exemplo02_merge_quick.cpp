/*
Exemplo 2. Ordenacoes eficientes O(n log n): Merge Sort e Quick Sort.
*/
#include <iostream>
using namespace std;

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }
void troca(int &a, int &b) { int t = a; a = b; b = t; }

// junta duas metades ja ordenadas
void intercala(int v[], int ini, int meio, int fim)
{
  int *aux = new int[fim - ini + 1], i = ini, j = meio + 1, k = 0;
  while (i <= meio && j <= fim) aux[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
  while (i <= meio) aux[k++] = v[i++];
  while (j <= fim) aux[k++] = v[j++];
  for (k = 0; k < fim - ini + 1; k++) v[ini + k] = aux[k];
  delete[] aux;
}

// divide ao meio, ordena cada metade e intercala
void mergeSort(int v[], int ini, int fim)
{
  if (ini >= fim) return;
  int meio = (ini + fim) / 2;
  mergeSort(v, ini, meio);
  mergeSort(v, meio + 1, fim);
  intercala(v, ini, meio, fim);
}

// pivo = ultimo; menores ficam a esquerda dele
int particiona(int v[], int ini, int fim)
{
  int pivo = v[fim], i = ini - 1;
  for (int j = ini; j < fim; j++) if (v[j] < pivo) troca(v[++i], v[j]);
  troca(v[i + 1], v[fim]);
  return i + 1;
}

void quickSort(int v[], int ini, int fim)
{
  if (ini >= fim) return;
  int p = particiona(v, ini, fim);
  quickSort(v, ini, p - 1);
  quickSort(v, p + 1, fim);
}

int main()
{
  int a[] = {38, 27, 43, 3, 9, 82, 10}, b[] = {38, 27, 43, 3, 9, 82, 10};
  mergeSort(a, 0, 6); imprime(a, 7);
  quickSort(b, 0, 6); imprime(b, 7);
  return 0;
}
