/*
Exemplo 2. Lista dinamica simplesmente encadeada.
*/
#include <iostream>
using namespace std;

// Lista simplesmente encadeada
struct No { int valor; No *prox; };

void insereInicio(No *&ini, int x) { No *n = new No; n->valor = x; n->prox = ini; ini = n; }

void insereFim(No *&ini, int x)
{
  No *n = new No; n->valor = x; n->prox = nullptr;
  if (ini == nullptr) { ini = n; return; }
  No *a = ini;
  while (a->prox != nullptr) a = a->prox;   // anda ate o ultimo
  a->prox = n;
}

bool remove(No *&ini, int x)
{
  No *ant = nullptr, *a = ini;
  while (a != nullptr && a->valor != x) { ant = a; a = a->prox; }
  if (a == nullptr) return false;           // nao achou
  if (ant == nullptr) ini = a->prox;        // era o primeiro
  else ant->prox = a->prox;                 // "pula" o no removido
  delete a;
  return true;
}

void imprime(No *ini) { for (No *a = ini; a != nullptr; a = a->prox) cout << a->valor << " "; cout << endl; }

void libera(No *&ini) { while (ini != nullptr) { No *a = ini; ini = ini->prox; delete a; } }

int main()
{
  No *l = nullptr;
  insereFim(l, 2); insereFim(l, 3); insereInicio(l, 1);
  imprime(l);   // 1 2 3
  remove(l, 2);
  imprime(l);   // 1 3
  libera(l);
  return 0;
}
