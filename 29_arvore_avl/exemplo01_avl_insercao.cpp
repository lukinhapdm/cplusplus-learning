/*
Exemplo 1. Arvore AVL (Adelson-Velsky e Landis): ABB em que, para todo no, |altura(esq) - altura(dir)| <= 1.
Fator de balanceamento fb = altura(esq) - altura(dir). Apos inserir, sobe pelo caminho atualizando alturas;
no primeiro no com |fb| = 2 aplica uma das quatro correcoes:
  - LL (fb = +2 e filho esq com fb >= 0): rotacao simples a direita
  - RR (fb = -2 e filho dir com fb <= 0): rotacao simples a esquerda
  - LR (fb = +2 e filho esq com fb < 0):  rotacao dupla (esquerda no filho, direita no no)
  - RL (fb = -2 e filho dir com fb > 0):  rotacao dupla (direita no filho, esquerda no no)
Altura garantida O(log n), entao busca, insercao e remocao custam O(log n).
*/
#include <iostream>
using namespace std;

struct No { int chave, altura; No *esq, *dir; };

class AVL {
  No *raiz = nullptr;

  static int alt(No *n) { return n ? n->altura : 0; }
  static int fb(No *n) { return alt(n->esq) - alt(n->dir); }
  static void atualiza(No *n) { int e = alt(n->esq), d = alt(n->dir); n->altura = 1 + (e > d ? e : d); }

  static No *rotDir(No *y)
  {
    No *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    atualiza(y); atualiza(x);
    return x;
  }

  static No *rotEsq(No *x)
  {
    No *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualiza(x); atualiza(y);
    return y;
  }

  static No *balanceia(No *n)
  {
    atualiza(n);
    if (fb(n) == 2) {
      if (fb(n->esq) < 0) { cout << "  LR em " << n->chave << endl; n->esq = rotEsq(n->esq); }
      else cout << "  LL em " << n->chave << endl;
      return rotDir(n);
    }
    if (fb(n) == -2) {
      if (fb(n->dir) > 0) { cout << "  RL em " << n->chave << endl; n->dir = rotDir(n->dir); }
      else cout << "  RR em " << n->chave << endl;
      return rotEsq(n);
    }
    return n;   // ja esta balanceado
  }

  No *insere(No *r, int k)
  {
    if (!r) return new No{k, 1, nullptr, nullptr};
    if (k < r->chave) r->esq = insere(r->esq, k);
    else if (k > r->chave) r->dir = insere(r->dir, k);
    else return r;
    return balanceia(r);   // corrige na volta da recursao
  }

  void desenha(No *r, int nivel)
  {
    if (!r) return;
    desenha(r->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "      ";
    cout << r->chave << "(" << fb(r) << ")" << endl;
    desenha(r->esq, nivel + 1);
  }
  void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

public:
  ~AVL() { libera(raiz); }
  void insere(int k) { cout << "insere " << k << endl; raiz = insere(raiz, k); }
  void desenha() { desenha(raiz, 0); }
  int altura() { return alt(raiz); }
};

int main()
{
  AVL a;
  int v[] = {10, 20, 30, 25, 28, 5, 3, 27};   // provoca os quatro casos
  for (int x : v) a.insere(x);
  cout << "\nArvore final, altura " << a.altura() << " - chave(fb):" << endl;
  a.desenha();
  return 0;
}
