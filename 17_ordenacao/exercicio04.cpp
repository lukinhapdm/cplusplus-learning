/*
Exercicio 4. Comparar o tempo do Selection Sort e do Quick Sort com 20000 numeros aleatorios.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }
void troca(int &a, int &b) { int t = a; a = b; b = t; }

void selection(int v[], int n)
{
  for (int i = 0; i < n - 1; i++) {
    int m = i;
    for (int j = i + 1; j < n; j++) if (v[j] < v[m]) m = j;
    troca(v[i], v[m]);
  }
}

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
  const int N = 20000;
  int *a = new int[N], *b = new int[N];
  srand(time(0));
  for (int i = 0; i < N; i++) a[i] = b[i] = rand() % 100000;   // mesmo vetor para os dois

  clock_t t = clock();   // marca o inicio
  selection(a, N);
  cout << "Selection: " << double(clock() - t) / CLOCKS_PER_SEC << " s" << endl;

  t = clock();
  quickSort(b, 0, N - 1);
  cout << "Quick:     " << double(clock() - t) / CLOCKS_PER_SEC << " s" << endl;

  delete[] a; delete[] b;
  return 0;
}
