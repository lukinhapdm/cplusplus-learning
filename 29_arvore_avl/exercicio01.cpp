/*
Exercicio 1. Inserir 1..n (em ordem crescente) em uma ABB comum e em uma AVL, para n = 10, 100 e 1000.
Mostrar a altura de cada uma e o numero de rotacoes feitas pela AVL.
*/
#include <iostream>
using namespace std;

struct No { int chave, altura; No *esq, *dir; };

int rotacoes = 0;

int alt(No *n) { return n ? n->altura : 0; }
int fb(No *n) { return alt(n->esq) - alt(n->dir); }
void atualiza(No *n) { int e = alt(n->esq), d = alt(n->dir); n->altura = 1 + (e > d ? e : d); }
No *rotDir(No *y) { rotacoes++; No *x = y->esq; y->esq = x->dir; x->dir = y; atualiza(y); atualiza(x); return x; }
No *rotEsq(No *x) { rotacoes++; No *y = x->dir; x->dir = y->esq; y->esq = x; atualiza(x); atualiza(y); return y; }

No *balanceia(No *n)
{
  atualiza(n);
  if (fb(n) > 1) { if (fb(n->esq) < 0) n->esq = rotEsq(n->esq); return rotDir(n); }
  if (fb(n) < -1) { if (fb(n->dir) > 0) n->dir = rotDir(n->dir); return rotEsq(n); }
  return n;
}

No *insereAVL(No *r, int k)
{
  if (!r) return new No{k, 1, nullptr, nullptr};
  if (k < r->chave) r->esq = insereAVL(r->esq, k);
  else if (k > r->chave) r->dir = insereAVL(r->dir, k);
  return balanceia(r);
}

// ABB comum, iterativa (a recursao ficaria profunda demais na arvore degenerada)
No *insereABB(No *r, int k)
{
  No **p = &r;
  while (*p) p = k < (*p)->chave ? &(*p)->esq : &(*p)->dir;
  *p = new No{k, 1, nullptr, nullptr};
  return r;
}

int altura(No *r)   // calcula sem usar o campo altura (que a ABB nao mantem)
{
  int h = 0;
  while (r) { h++; r = r->dir ? r->dir : r->esq; }   // valido aqui: ABB degenerada
  return h;
}

void libera(No *r)
{
  while (r) {   // libera sem recursao profunda: rotaciona ate nao ter filho esquerdo
    if (r->esq) { No *e = r->esq; r->esq = e->dir; e->dir = r; r = e; }
    else { No *d = r->dir; delete r; r = d; }
  }
}

int main()
{
  for (int n : {10, 100, 1000}) {
    No *abb = nullptr, *avl = nullptr;
    rotacoes = 0;
    for (int k = 1; k <= n; k++) { abb = insereABB(abb, k); avl = insereAVL(avl, k); }
    cout << "n = " << n << ": altura ABB = " << altura(abb) << ", altura AVL = " << alt(avl)
         << ", rotacoes AVL = " << rotacoes << endl;
    libera(abb); libera(avl);
  }
  return 0;
}
