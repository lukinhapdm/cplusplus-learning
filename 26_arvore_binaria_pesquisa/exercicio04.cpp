/*
Exercicio 4. Implementar insercao e busca em ABB sem recursao, usando ponteiro para ponteiro
(No **) para apontar o lugar onde o novo no deve ser ligado.
*/
#include <iostream>
using namespace std;

struct No { int chave; No *esq, *dir; };

bool insere(No **raiz, int k)
{
  No **p = raiz;
  while (*p) {
    if (k == (*p)->chave) return false;   // ja existe
    p = k < (*p)->chave ? &(*p)->esq : &(*p)->dir;
  }
  *p = new No{k, nullptr, nullptr};       // *p e o ponteiro nulo onde o no sera ligado
  return true;
}

No *busca(No *r, int k, int &comp)
{
  comp = 0;
  while (r) {
    comp++;
    if (k == r->chave) return r;
    r = k < r->chave ? r->esq : r->dir;
  }
  return nullptr;
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *raiz = nullptr;
  int v[] = {8, 3, 10, 1, 6, 14, 4, 7, 13, 6};
  for (int x : v) if (!insere(&raiz, x)) cout << x << " repetido" << endl;
  int comp;
  for (int k : {7, 13, 5}) {
    No *n = busca(raiz, k, comp);
    cout << k << (n ? " encontrado" : " nao encontrado") << " com " << comp << " comparacoes" << endl;
  }
  libera(raiz);
  return 0;
}
