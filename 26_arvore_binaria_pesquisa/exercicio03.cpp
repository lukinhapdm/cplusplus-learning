/*
Exercicio 3. Percorrer uma ABB em largura (nivel a nivel) usando uma fila, imprimindo uma linha por nivel.
*/
#include <iostream>
#include <queue>
using namespace std;

struct No { int chave; No *esq, *dir; };

No *insere(No *r, int k)
{
  if (!r) return new No{k, nullptr, nullptr};
  if (k < r->chave) r->esq = insere(r->esq, k);
  else if (k > r->chave) r->dir = insere(r->dir, k);
  return r;
}

void largura(No *r)
{
  if (!r) return;
  queue<No *> f;
  f.push(r);
  int nivel = 0;
  while (!f.empty()) {
    int qtd = f.size();   // quantidade de nos do nivel atual
    cout << "Nivel " << nivel++ << ": ";
    for (int i = 0; i < qtd; i++) {
      No *a = f.front(); f.pop();
      cout << a->chave << " ";
      if (a->esq) f.push(a->esq);
      if (a->dir) f.push(a->dir);
    }
    cout << endl;
  }
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *r = nullptr;
  int v[] = {40, 20, 60, 10, 30, 50, 70, 25, 55, 65};
  for (int x : v) r = insere(r, x);
  largura(r);
  libera(r);
  return 0;
}
