/*
Exercicio 1. Verificar se um vetor e um heap maximo. Depois implementar alteraPrioridade(i, novo):
se o valor aumentou, o elemento sobe; se diminuiu, desce.
*/
#include <iostream>
#include <utility>
using namespace std;

bool ehHeapMax(int v[], int n)
{
  for (int i = 1; i < n; i++) if (v[(i - 1) / 2] < v[i]) return false;   // todo filho <= pai
  return true;
}

void sobe(int v[], int i) { while (i > 0 && v[(i - 1) / 2] < v[i]) { swap(v[i], v[(i - 1) / 2]); i = (i - 1) / 2; } }

void desce(int v[], int n, int i)
{
  while (2 * i + 1 < n) {
    int f = 2 * i + 1;
    if (f + 1 < n && v[f + 1] > v[f]) f++;
    if (v[i] >= v[f]) break;
    swap(v[i], v[f]); i = f;
  }
}

void alteraPrioridade(int v[], int n, int i, int novo)
{
  int antigo = v[i];
  v[i] = novo;
  if (novo > antigo) sobe(v, i);
  else desce(v, n, i);
}

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }

int main()
{
  int a[] = {90, 15, 10, 7, 16, 2, 7, 3};   // 16 > 15 (pai)
  int b[] = {90, 70, 60, 30, 50, 40, 20, 10};
  cout << "a e heap? " << ehHeapMax(a, 8) << "   b e heap? " << ehHeapMax(b, 8) << endl;

  alteraPrioridade(b, 8, 7, 95);   // o 10 vira 95 e sobe ate a raiz
  cout << "10 -> 95: "; imprime(b, 8);
  alteraPrioridade(b, 8, 0, 5);    // a raiz vira 5 e desce
  cout << "95 -> 5:  "; imprime(b, 8);
  cout << "continua heap? " << ehHeapMax(b, 8) << endl;
  return 0;
}
