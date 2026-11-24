/*
Exercicio 2. A STL usa arvore vermelho-preto em set e map. Comparar, para n = 1000, 10000 e 100000 chaves
inseridas em ordem crescente, a altura de uma vermelho-preto propria, o limite 2 log2(n + 1) e o numero
de rotacoes. Mostrar tambem a proporcao de nos vermelhos.
*/
#include <iostream>
#include <cmath>
using namespace std;

enum Cor { VERMELHO, PRETO };
struct No { int chave; Cor cor; No *esq, *dir, *pai; };

No *NIL = new No{0, PRETO, nullptr, nullptr, nullptr};
No *raiz = NIL;
long rotacoes = 0;

void rotEsq(No *x)
{
  rotacoes++;
  No *y = x->dir; x->dir = y->esq;
  if (y->esq != NIL) y->esq->pai = x;
  y->pai = x->pai;
  if (x->pai == NIL) raiz = y; else if (x == x->pai->esq) x->pai->esq = y; else x->pai->dir = y;
  y->esq = x; x->pai = y;
}

void rotDir(No *x)
{
  rotacoes++;
  No *y = x->esq; x->esq = y->dir;
  if (y->dir != NIL) y->dir->pai = x;
  y->pai = x->pai;
  if (x->pai == NIL) raiz = y; else if (x == x->pai->dir) x->pai->dir = y; else x->pai->esq = y;
  y->dir = x; x->pai = y;
}

void insere(int k)
{
  No *p = NIL, *x = raiz;
  while (x != NIL) { p = x; if (k == x->chave) return; x = k < x->chave ? x->esq : x->dir; }
  No *z = new No{k, VERMELHO, NIL, NIL, p};
  if (p == NIL) raiz = z; else if (k < p->chave) p->esq = z; else p->dir = z;
  while (z->pai->cor == VERMELHO) {
    No *a = z->pai->pai;
    bool esq = z->pai == a->esq;
    No *tio = esq ? a->dir : a->esq;
    if (tio->cor == VERMELHO) { z->pai->cor = tio->cor = PRETO; a->cor = VERMELHO; z = a; }
    else {
      if (esq && z == z->pai->dir) { z = z->pai; rotEsq(z); }
      else if (!esq && z == z->pai->esq) { z = z->pai; rotDir(z); }
      z->pai->cor = PRETO; a->cor = VERMELHO;
      if (esq) rotDir(a); else rotEsq(a);
    }
  }
  raiz->cor = PRETO;
}

int altura(No *r) { if (r == NIL) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
int vermelhos(No *r) { return r == NIL ? 0 : (r->cor == VERMELHO) + vermelhos(r->esq) + vermelhos(r->dir); }
void libera(No *r) { if (r != NIL) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  for (int n : {1000, 10000, 100000}) {
    raiz = NIL; rotacoes = 0;
    for (int k = 1; k <= n; k++) insere(k);
    cout << "n = " << n << ": altura = " << altura(raiz) << " (limite " << 2 * log2(n + 1.0)
         << ", minimo possivel " << (int)ceil(log2(n + 1.0)) << "), rotacoes = " << rotacoes
         << ", vermelhos = " << 100.0 * vermelhos(raiz) / n << "%" << endl;
    libera(raiz);
  }
  delete NIL;
  return 0;
}
