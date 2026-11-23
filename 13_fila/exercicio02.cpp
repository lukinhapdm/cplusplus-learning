/*
Exercicio 2. Inverter os elementos de uma fila usando uma pilha auxiliar.
*/
#include <iostream>
using namespace std;

// Fila dinamica: guarda ponteiro para o inicio e para o fim
struct No { int valor; No *prox; };
struct Fila { No *ini, *fim; };

void inicia(Fila &f) { f.ini = f.fim = nullptr; }
bool vazia(Fila &f) { return f.ini == nullptr; }

void enfileira(Fila &f, int x)
{
  No *n = new No; n->valor = x; n->prox = nullptr;
  if (vazia(f)) f.ini = n;   // primeiro elemento
  else f.fim->prox = n;      // liga no final
  f.fim = n;
}

bool desenfileira(Fila &f, int &x)
{
  if (vazia(f)) return false;
  No *aux = f.ini;
  x = aux->valor;
  f.ini = aux->prox;
  if (f.ini == nullptr) f.fim = nullptr;   // ficou vazia
  delete aux;
  return true;
}

// pilha simples encadeada para auxiliar
struct NoP { int valor; NoP *prox; };
void empilha(NoP *&t, int x) { NoP *n = new NoP; n->valor = x; n->prox = t; t = n; }
int desempilha(NoP *&t) { NoP *a = t; int x = a->valor; t = a->prox; delete a; return x; }

void inverte(Fila &f)
{
  NoP *topo = nullptr; int x;
  while (desenfileira(f, x)) empilha(topo, x);         // fila -> pilha
  while (topo != nullptr) enfileira(f, desempilha(topo)); // pilha -> fila (ordem invertida)
}

int main()
{
  Fila f; inicia(f); int x;
  for (int i = 1; i <= 5; i++) enfileira(f, i);
  inverte(f);
  while (desenfileira(f, x)) cout << x << " ";   // 5 4 3 2 1
  cout << endl;
  return 0;
}
