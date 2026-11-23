/*
Exercicio 1. Lista estatica ordenada: inserir mantendo a ordem crescente.
*/
#include <iostream>
using namespace std;

const int MAX = 100;
struct Lista { int dados[MAX]; int n; };

bool insereOrdenado(Lista &l, int x)
{
  if (l.n == MAX) return false;
  int i = l.n;
  // desloca para a direita todos os maiores que x
  while (i > 0 && l.dados[i - 1] > x) { l.dados[i] = l.dados[i - 1]; i--; }
  l.dados[i] = x;
  l.n++;
  return true;
}

int main()
{
  Lista l; l.n = 0; int x;
  cout << "Digite 6 valores: ";
  for (int i = 0; i < 6; i++) { cin >> x; insereOrdenado(l, x); }
  for (int i = 0; i < l.n; i++) cout << l.dados[i] << " ";
  cout << endl;
  return 0;
}
