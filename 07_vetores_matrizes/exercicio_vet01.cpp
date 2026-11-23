/*
7.1.4 Exercício 1. Dois vetores de 10: interseção, união e diferença (sem repetidos).
*/
#include <iostream>
using namespace std;

// verifica se x esta no vetor v de tamanho n
bool existe(int v[], int n, int x)
{
  for (int i = 0; i < n; i++) if (v[i] == x) return true;
  return false;
}

// adiciona x ao vetor r somente se ainda nao estiver la (evita repetidos)
void adiciona(int r[], int &n, int x) { if (!existe(r, n, x)) r[n++] = x; }

void mostra(const char *nome, int r[], int n)
{
  cout << nome << ": ";
  for (int i = 0; i < n; i++) cout << r[i] << " ";
  cout << endl;
}

int main()
{
  int a[10], b[10], inter[10], uni[20], dif[10], ni = 0, nu = 0, nd = 0;
  cout << "10 valores do vetor A: "; for (int i = 0; i < 10; i++) cin >> a[i];
  cout << "10 valores do vetor B: "; for (int i = 0; i < 10; i++) cin >> b[i];
  for (int i = 0; i < 10; i++) {
    if (existe(b, 10, a[i])) adiciona(inter, ni, a[i]);   // em A e em B
    else adiciona(dif, nd, a[i]);                         // so em A
    adiciona(uni, nu, a[i]);
    adiciona(uni, nu, b[i]);
  }
  mostra("Intersecao", inter, ni);
  mostra("Uniao", uni, nu);
  mostra("A - B", dif, nd);
  return 0;
}
