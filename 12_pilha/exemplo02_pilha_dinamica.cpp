/*
Exemplo 2. Pilha dinamica (encadeada), sem limite fixo de tamanho.
*/
#include <iostream>
using namespace std;

// Pilha dinamica: cada no aponta para o de baixo
struct No { int valor; No *prox; };
struct Pilha { No *topo; };

void inicia(Pilha &p) { p.topo = nullptr; }
bool vazia(Pilha &p) { return p.topo == nullptr; }

void empilha(Pilha &p, int x)
{
  No *n = new No;
  n->valor = x;
  n->prox = p.topo;   // novo no aponta para o antigo topo
  p.topo = n;
}

bool desempilha(Pilha &p, int &x)
{
  if (vazia(p)) return false;
  No *aux = p.topo;
  x = aux->valor;
  p.topo = aux->prox;
  delete aux;         // libera o no removido
  return true;
}

int main()
{
  Pilha p; int x;
  inicia(p);
  empilha(p, 1); empilha(p, 2); empilha(p, 3);
  while (desempilha(p, x)) cout << x << " ";   // 3 2 1
  cout << endl;
  return 0;
}
