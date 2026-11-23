/*
Exercicio 1. Usando uma pilha, converter um numero decimal para binario.
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
  Pilha p; int n, x;
  inicia(p);
  cout << "Numero decimal: "; cin >> n;
  if (n == 0) empilha(p, 0);
  // os restos saem do menos para o mais significativo; a pilha inverte a ordem
  while (n > 0) { empilha(p, n % 2); n /= 2; }
  cout << "Binario: ";
  while (desempilha(p, x)) cout << x;
  cout << endl;
  return 0;
}
