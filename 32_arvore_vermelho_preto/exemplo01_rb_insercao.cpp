/*
Exemplo 1. Arvore vermelho-preto (rubro-negra): ABB em que cada no e VERMELHO ou PRETO e valem as regras
  1) a raiz e preta;
  2) as folhas nulas (NIL) sao pretas;
  3) um no vermelho nao tem filho vermelho;
  4) todo caminho de um no ate as folhas NIL tem o mesmo numero de nos pretos (altura negra).
Consequencia: altura <= 2 log2(n + 1). E menos rigida que a AVL (menos rotacoes na insercao/remocao).
Insercao: insere como na ABB com cor vermelha e corrige violacoes da regra 3 olhando o "tio":
  - caso 1, tio vermelho: recolore pai e tio de preto, avo de vermelho e continua a partir do avo;
  - caso 2, tio preto e no "em zigue-zague": rotaciona o pai para cair no caso 3;
  - caso 3, tio preto e no "em linha": rotaciona o avo e troca as cores de pai e avo.
Usa um no sentinela NIL (preto) no lugar de nullptr, o que simplifica os testes de cor.
*/
#include <iostream>
using namespace std;

enum Cor { VERMELHO, PRETO };
struct No { int chave; Cor cor; No *esq, *dir, *pai; };

class RubroNegra {
  No *NIL, *raiz;

  void rotEsq(No *x)
  {
    No *y = x->dir;
    x->dir = y->esq;
    if (y->esq != NIL) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NIL) raiz = y;
    else if (x == x->pai->esq) x->pai->esq = y;
    else x->pai->dir = y;
    y->esq = x;
    x->pai = y;
  }

  void rotDir(No *x)
  {
    No *y = x->esq;
    x->esq = y->dir;
    if (y->dir != NIL) y->dir->pai = x;
    y->pai = x->pai;
    if (x->pai == NIL) raiz = y;
    else if (x == x->pai->dir) x->pai->dir = y;
    else x->pai->esq = y;
    y->dir = x;
    x->pai = y;
  }

  void corrigeInsercao(No *z)
  {
    while (z->pai->cor == VERMELHO) {   // violacao: pai e filho vermelhos
      No *avo = z->pai->pai;
      if (z->pai == avo->esq) {
        No *tio = avo->dir;
        if (tio->cor == VERMELHO) {                         // caso 1
          z->pai->cor = PRETO; tio->cor = PRETO; avo->cor = VERMELHO;
          z = avo;
        } else {
          if (z == z->pai->dir) { z = z->pai; rotEsq(z); }   // caso 2
          z->pai->cor = PRETO; avo->cor = VERMELHO;          // caso 3
          rotDir(avo);
        }
      } else {   // simetrico: pai e filho direito do avo
        No *tio = avo->esq;
        if (tio->cor == VERMELHO) {
          z->pai->cor = PRETO; tio->cor = PRETO; avo->cor = VERMELHO;
          z = avo;
        } else {
          if (z == z->pai->esq) { z = z->pai; rotDir(z); }
          z->pai->cor = PRETO; avo->cor = VERMELHO;
          rotEsq(avo);
        }
      }
    }
    raiz->cor = PRETO;   // regra 1
  }

  void desenha(No *r, int nivel)
  {
    if (r == NIL) return;
    desenha(r->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "      ";
    cout << r->chave << (r->cor == VERMELHO ? "(V)" : "(P)") << endl;
    desenha(r->esq, nivel + 1);
  }

  int altura(No *r) { if (r == NIL) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
  void libera(No *r) { if (r != NIL) { libera(r->esq); libera(r->dir); delete r; } }

public:
  RubroNegra()
  {
    NIL = new No{0, PRETO, nullptr, nullptr, nullptr};
    raiz = NIL;
  }
  ~RubroNegra() { libera(raiz); delete NIL; }

  void insere(int k)
  {
    No *pai = NIL, *x = raiz;
    while (x != NIL) {   // desce como na ABB
      pai = x;
      if (k == x->chave) return;
      x = k < x->chave ? x->esq : x->dir;
    }
    No *z = new No{k, VERMELHO, NIL, NIL, pai};
    if (pai == NIL) raiz = z;
    else if (k < pai->chave) pai->esq = z;
    else pai->dir = z;
    corrigeInsercao(z);
  }

  bool busca(int k)
  {
    No *x = raiz;
    while (x != NIL && x->chave != k) x = k < x->chave ? x->esq : x->dir;
    return x != NIL;
  }

  void desenha() { desenha(raiz, 0); }
  int altura() { return altura(raiz); }
};

int main()
{
  RubroNegra t;
  for (int k = 1; k <= 10; k++) t.insere(k);   // em ordem crescente: na ABB seria uma lista
  t.desenha();
  cout << "Altura: " << t.altura() << ", busca(7) = " << t.busca(7) << endl;
  return 0;
}
