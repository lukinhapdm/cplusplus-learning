/*
Exemplo 1. Pilha estatica (vetor) com empilha, desempilha e consulta.
*/
#include <iostream>
using namespace std;

// Pilha estatica: o ultimo que entra e o primeiro que sai (LIFO)
const int MAX = 100;
struct Pilha { int dados[MAX]; int topo; };   // topo = qtd de elementos

void inicia(Pilha &p) { p.topo = 0; }
bool vazia(Pilha &p) { return p.topo == 0; }
bool cheia(Pilha &p) { return p.topo == MAX; }
bool empilha(Pilha &p, int x) { if (cheia(p)) return false; p.dados[p.topo++] = x; return true; }
bool desempilha(Pilha &p, int &x) { if (vazia(p)) return false; x = p.dados[--p.topo]; return true; }

int main()
{
  Pilha p; int x;
  inicia(p);
  for (int i = 1; i <= 5; i++) empilha(p, i * 10);
  cout << "Desempilhando: ";
  while (desempilha(p, x)) cout << x << " ";   // sai na ordem inversa: 50 40 30 20 10
  cout << endl;
  return 0;
}
