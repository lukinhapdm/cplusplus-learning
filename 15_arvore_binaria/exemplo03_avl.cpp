/*
Exemplo 3. Arvore AVL: arvore de busca que se rebalanceia com rotacoes (diferenca de altura entre os lados no maximo 1).
*/
#include <iostream>
using namespace std;

struct No { int valor, altura; No *esq, *dir; };

int alt(No *n) { return n ? n->altura : 0; }
int maxi(int a, int b) { return a > b ? a : b; }
void atualiza(No *n) { n->altura = 1 + maxi(alt(n->esq), alt(n->dir)); }
int fb(No *n) { return alt(n->esq) - alt(n->dir); }   // fator de balanceamento

// rotacao a direita: o filho esquerdo sobe
No *rotDir(No *y)
{
  No *x = y->esq;
  y->esq = x->dir;
  x->dir = y;
  atualiza(y); atualiza(x);
  return x;
}

// rotacao a esquerda: o filho direito sobe
No *rotEsq(No *x)
{
  No *y = x->dir;
  x->dir = y->esq;
  y->esq = x;
  atualiza(x); atualiza(y);
  return y;
}

No *insere(No *r, int v)
{
  if (!r) return new No{v, 1, nullptr, nullptr};
  if (v < r->valor) r->esq = insere(r->esq, v);
  else if (v > r->valor) r->dir = insere(r->dir, v);
  else return r;                       // nao aceita repetido
  atualiza(r);
  int b = fb(r);
  // 4 casos de desbalanceamento
  if (b > 1 && v < r->esq->valor) return rotDir(r);                                  // esq-esq
  if (b < -1 && v > r->dir->valor) return rotEsq(r);                                 // dir-dir
  if (b > 1 && v > r->esq->valor) { r->esq = rotEsq(r->esq); return rotDir(r); }     // esq-dir
  if (b < -1 && v < r->dir->valor) { r->dir = rotDir(r->dir); return rotEsq(r); }    // dir-esq
  return r;
}

void preOrdem(No *r) { if (r) { cout << r->valor << " "; preOrdem(r->esq); preOrdem(r->dir); } }
void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *raiz = nullptr;
  // inserir em ordem crescente deixaria uma ABB comum "torta" (altura 7)
  for (int i = 1; i <= 7; i++) raiz = insere(raiz, i);
  cout << "Raiz: " << raiz->valor << " | Altura: " << alt(raiz) << endl;   // raiz 4, altura 3
  preOrdem(raiz); cout << endl;
  libera(raiz);
  return 0;
}
