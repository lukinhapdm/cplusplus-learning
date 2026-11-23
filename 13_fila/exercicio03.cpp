/*
Exercicio 3. Ler 10 inteiros em uma fila e depois separar em duas filas: uma com os pares e outra com os impares, mantendo a ordem.
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

void mostra(Fila &f) { int x; while (desenfileira(f, x)) cout << x << " "; cout << endl; }

int main()
{
  Fila f, pares, impares; int x;
  inicia(f); inicia(pares); inicia(impares);
  cout << "10 inteiros: ";
  for (int i = 0; i < 10; i++) { cin >> x; enfileira(f, x); }
  // tira da fila original e coloca na fila certa
  while (desenfileira(f, x)) {
    if (x % 2 == 0) enfileira(pares, x);
    else enfileira(impares, x);
  }
  cout << "Pares: "; mostra(pares);
  cout << "Impares: "; mostra(impares);
  return 0;
}
