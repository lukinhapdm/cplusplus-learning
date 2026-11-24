/*
Exercicio 3. Arvore 2-3-4 x vermelho-preto: cada no preto junto com seus filhos vermelhos corresponde
a um no de uma arvore 2-3-4 (B de ordem 4). Inserir algumas chaves e imprimir, nivel por nivel,
os "nos 2-3-4" equivalentes, ex.: [10 20 30] = preto 20 com filhos vermelhos 10 e 30.
*/
#include <iostream>
#include <vector>
using namespace std;

enum Cor { VERMELHO, PRETO };
struct No { int chave; Cor cor; No *esq, *dir, *pai; };

No *NIL = new No{0, PRETO, nullptr, nullptr, nullptr};
No *raiz = NIL;

void rotEsq(No *x)
{
  No *y = x->dir; x->dir = y->esq;
  if (y->esq != NIL) y->esq->pai = x;
  y->pai = x->pai;
  if (x->pai == NIL) raiz = y; else if (x == x->pai->esq) x->pai->esq = y; else x->pai->dir = y;
  y->esq = x; x->pai = y;
}

void rotDir(No *x)
{
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

// junta um no preto com seus filhos vermelhos; os filhos pretos (ou NIL) desses viram os filhos do no 2-3-4
void no234(No *p, vector<int> &chaves, vector<No *> &filhos)
{
  if (p->esq->cor == VERMELHO) {
    chaves.push_back(p->esq->chave);
    filhos.push_back(p->esq->esq); filhos.push_back(p->esq->dir);
  } else filhos.push_back(p->esq);
  chaves.push_back(p->chave);
  if (p->dir->cor == VERMELHO) {
    chaves.push_back(p->dir->chave);
    filhos.push_back(p->dir->esq); filhos.push_back(p->dir->dir);
  } else filhos.push_back(p->dir);
}

void imprime234()
{
  vector<No *> nivel = {raiz};
  while (!nivel.empty() && nivel[0] != NIL) {
    vector<No *> prox;
    for (No *p : nivel) {
      vector<int> ch; vector<No *> fi;
      no234(p, ch, fi);
      cout << "[";
      for (size_t i = 0; i < ch.size(); i++) cout << (i ? " " : "") << ch[i];
      cout << "] ";
      for (No *f : fi) if (f != NIL) prox.push_back(f);
    }
    cout << endl;
    nivel = prox;
  }
}

void libera(No *r) { if (r != NIL) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  for (int k : {10, 20, 30, 40, 50, 60, 70, 80, 5, 15, 25}) insere(k);
  imprime234();
  libera(raiz); delete NIL;
  return 0;
}
