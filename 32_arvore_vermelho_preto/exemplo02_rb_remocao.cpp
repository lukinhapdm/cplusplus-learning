/*
Exemplo 2. Remocao em arvore vermelho-preto. Remove como na ABB usando "transplante" (troca uma subarvore
por outra). Se o no que saiu da arvore era PRETO, um caminho perdeu um preto: o no x que ocupou o lugar
fica com um "preto extra", corrigido com quatro casos olhando o irmao w de x:
  - caso 1, w vermelho: rotaciona o pai e recolore, caindo em um dos outros casos;
  - caso 2, w preto com dois filhos pretos: pinta w de vermelho e sobe o problema para o pai;
  - caso 3, w preto, filho "de fora" preto e "de dentro" vermelho: rotaciona w, caindo no caso 4;
  - caso 4, w preto com filho "de fora" vermelho: rotaciona o pai, recolore e termina.
*/
#include <iostream>
using namespace std;

enum Cor { VERMELHO, PRETO };
struct No { int chave; Cor cor; No *esq, *dir, *pai; };

No *NIL = new No{0, PRETO, nullptr, nullptr, nullptr};
No *raiz = NIL;

void rotEsq(No *x)
{
  No *y = x->dir;
  x->dir = y->esq;
  if (y->esq != NIL) y->esq->pai = x;
  y->pai = x->pai;
  if (x->pai == NIL) raiz = y; else if (x == x->pai->esq) x->pai->esq = y; else x->pai->dir = y;
  y->esq = x; x->pai = y;
}

void rotDir(No *x)
{
  No *y = x->esq;
  x->esq = y->dir;
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

// coloca v no lugar de u (u sai da arvore)
void transplante(No *u, No *v)
{
  if (u->pai == NIL) raiz = v;
  else if (u == u->pai->esq) u->pai->esq = v;
  else u->pai->dir = v;
  v->pai = u->pai;   // vale mesmo se v for NIL (o sentinela guarda o pai temporariamente)
}

void corrigeRemocao(No *x)
{
  while (x != raiz && x->cor == PRETO) {   // x carrega um preto extra
    if (x == x->pai->esq) {
      No *w = x->pai->dir;
      if (w->cor == VERMELHO) {                                       // caso 1
        w->cor = PRETO; x->pai->cor = VERMELHO; rotEsq(x->pai); w = x->pai->dir;
      }
      if (w->esq->cor == PRETO && w->dir->cor == PRETO) {             // caso 2
        w->cor = VERMELHO; x = x->pai;
      } else {
        if (w->dir->cor == PRETO) {                                   // caso 3
          w->esq->cor = PRETO; w->cor = VERMELHO; rotDir(w); w = x->pai->dir;
        }
        w->cor = x->pai->cor; x->pai->cor = PRETO; w->dir->cor = PRETO; // caso 4
        rotEsq(x->pai);
        x = raiz;
      }
    } else {   // simetrico
      No *w = x->pai->esq;
      if (w->cor == VERMELHO) { w->cor = PRETO; x->pai->cor = VERMELHO; rotDir(x->pai); w = x->pai->esq; }
      if (w->dir->cor == PRETO && w->esq->cor == PRETO) { w->cor = VERMELHO; x = x->pai; }
      else {
        if (w->esq->cor == PRETO) { w->dir->cor = PRETO; w->cor = VERMELHO; rotEsq(w); w = x->pai->esq; }
        w->cor = x->pai->cor; x->pai->cor = PRETO; w->esq->cor = PRETO;
        rotDir(x->pai);
        x = raiz;
      }
    }
  }
  x->cor = PRETO;
}

void remove(int k)
{
  No *z = raiz;
  while (z != NIL && z->chave != k) z = k < z->chave ? z->esq : z->dir;
  if (z == NIL) return;

  No *y = z, *x;              // y: no que sai fisicamente da sua posicao
  Cor corOriginal = y->cor;
  if (z->esq == NIL) { x = z->dir; transplante(z, z->dir); }
  else if (z->dir == NIL) { x = z->esq; transplante(z, z->esq); }
  else {
    y = z->dir;
    while (y->esq != NIL) y = y->esq;   // sucessor
    corOriginal = y->cor;
    x = y->dir;
    if (y->pai == z) x->pai = y;
    else { transplante(y, y->dir); y->dir = z->dir; y->dir->pai = y; }
    transplante(z, y);
    y->esq = z->esq; y->esq->pai = y;
    y->cor = z->cor;                    // o sucessor herda a cor de z
  }
  delete z;
  if (corOriginal == PRETO) corrigeRemocao(x);   // so remover preto quebra a altura negra
}

void desenha(No *r, int nivel = 0)
{
  if (r == NIL) return;
  desenha(r->dir, nivel + 1);
  for (int i = 0; i < nivel; i++) cout << "      ";
  cout << r->chave << (r->cor == VERMELHO ? "(V)" : "(P)") << endl;
  desenha(r->esq, nivel + 1);
}

void libera(No *r) { if (r != NIL) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  for (int k : {20, 10, 30, 5, 15, 25, 40, 35, 50}) insere(k);
  cout << "Inicial:" << endl; desenha(raiz);
  remove(5);    // folha vermelha: nao precisa de correcao
  cout << "\nApos remover 5:" << endl; desenha(raiz);
  remove(25);   // folha preta: o caminho perde um preto e precisa de correcao
  cout << "\nApos remover 25:" << endl; desenha(raiz);
  remove(20);   // raiz com dois filhos: troca pelo sucessor
  cout << "\nApos remover 20:" << endl; desenha(raiz);
  libera(raiz); delete NIL;
  return 0;
}
