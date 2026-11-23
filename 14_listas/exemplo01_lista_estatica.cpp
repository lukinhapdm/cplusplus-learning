/*
Exemplo 1. Lista linear estatica (vetor): insere no fim, insere em posicao, remove e busca.
*/
#include <iostream>
using namespace std;

const int MAX = 100;
struct Lista { int dados[MAX]; int n; };   // n = quantidade de elementos

void inicia(Lista &l) { l.n = 0; }

bool insereFim(Lista &l, int x) { if (l.n == MAX) return false; l.dados[l.n++] = x; return true; }

// abre espaco deslocando os elementos para a direita
bool inserePos(Lista &l, int pos, int x)
{
  if (l.n == MAX || pos < 0 || pos > l.n) return false;
  for (int i = l.n; i > pos; i--) l.dados[i] = l.dados[i - 1];
  l.dados[pos] = x; l.n++;
  return true;
}

int busca(Lista &l, int x) { for (int i = 0; i < l.n; i++) if (l.dados[i] == x) return i; return -1; }

// fecha o buraco deslocando para a esquerda
bool remove(Lista &l, int x)
{
  int p = busca(l, x);
  if (p == -1) return false;
  for (int i = p; i < l.n - 1; i++) l.dados[i] = l.dados[i + 1];
  l.n--;
  return true;
}

void imprime(Lista &l) { for (int i = 0; i < l.n; i++) cout << l.dados[i] << " "; cout << endl; }

int main()
{
  Lista l; inicia(l);
  insereFim(l, 10); insereFim(l, 30); inserePos(l, 1, 20);
  imprime(l);   // 10 20 30
  remove(l, 10);
  imprime(l);   // 20 30
  return 0;
}
