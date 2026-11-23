/*
Exercicio 3. Inverter uma lista encadeada sem criar novos nos (apenas trocando os ponteiros).
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

void inverte(No *&ini)
{
  No *ant = nullptr, *a = ini, *prox;
  while (a != nullptr) {
    prox = a->prox;   // guarda o proximo antes de perder a referencia
    a->prox = ant;    // vira a seta para tras
    ant = a;
    a = prox;
  }
  ini = ant;          // o ultimo virou o primeiro
}

int main()
{
  No *l = nullptr;
  for (int i = 1; i <= 5; i++) insereFim(l, i);
  inverte(l);
  imprime(l);   // 5 4 3 2 1
  libera(l);
  return 0;
}
