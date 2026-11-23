/*
Exercicio 1. Adicionar ao hash com encadeamento uma funcao de remocao de chave.
*/
#include <iostream>
using namespace std;

// Hash com encadeamento: cada posicao guarda uma lista
const int TAM = 7;
struct No { int chave; No *prox; };

int h(int chave) { return chave % TAM; }

void insere(No *t[], int chave)
{
  No *n = new No; n->chave = chave;
  n->prox = t[h(chave)];   // insere no inicio da lista daquela posicao
  t[h(chave)] = n;
}

bool busca(No *t[], int chave)
{
  for (No *a = t[h(chave)]; a; a = a->prox) if (a->chave == chave) return true;
  return false;
}

void imprime(No *t[])
{
  for (int i = 0; i < TAM; i++) {
    cout << i << ": ";
    for (No *a = t[i]; a; a = a->prox) cout << a->chave << " -> ";
    cout << "null" << endl;
  }
}

bool remove(No *t[], int chave)
{
  No *ant = nullptr, *a = t[h(chave)];
  while (a && a->chave != chave) { ant = a; a = a->prox; }
  if (!a) return false;
  if (ant) ant->prox = a->prox;   // tira do meio/fim da lista
  else t[h(chave)] = a->prox;     // era o primeiro da lista
  delete a;
  return true;
}

int main()
{
  No *t[TAM] = {nullptr};
  int v[] = {10, 17, 24, 3};
  for (int x : v) insere(t, x);
  remove(t, 17);
  imprime(t);
  return 0;
}
