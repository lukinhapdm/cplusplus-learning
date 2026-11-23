/*
Exercicio 2. Na lista encadeada, criar funcoes para contar os elementos e somar os valores.
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

int conta(No *ini) { int c = 0; for (No *a = ini; a; a = a->prox) c++; return c; }
int soma(No *ini) { int s = 0; for (No *a = ini; a; a = a->prox) s += a->valor; return s; }

int main()
{
  No *l = nullptr;
  for (int i = 1; i <= 5; i++) insereFim(l, i);
  cout << "Elementos: " << conta(l) << " | Soma: " << soma(l) << endl;
  libera(l);
  return 0;
}
