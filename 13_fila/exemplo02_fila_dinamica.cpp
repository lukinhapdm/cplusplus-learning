/*
Exemplo 2. Fila dinamica (encadeada).
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

int main()
{
  Fila f; int x;
  inicia(f);
  enfileira(f, 10); enfileira(f, 20); enfileira(f, 30);
  while (desenfileira(f, x)) cout << x << " ";   // 10 20 30
  cout << endl;
  return 0;
}
