/*
Exemplo 2. Remocao em AVL. Remove como na ABB (folha, um filho ou troca pelo sucessor) e, na volta da
recursao, rebalanceia cada no do caminho. Diferente da insercao, a remocao pode exigir rotacoes em
varios niveis (ate O(log n) rotacoes).
*/
#include <iostream>
using namespace std;

struct No { int chave, altura; No *esq, *dir; };

int alt(No *n) { return n ? n->altura : 0; }
int fb(No *n) { return alt(n->esq) - alt(n->dir); }
void atualiza(No *n) { int e = alt(n->esq), d = alt(n->dir); n->altura = 1 + (e > d ? e : d); }

No *rotDir(No *y) { No *x = y->esq; y->esq = x->dir; x->dir = y; atualiza(y); atualiza(x); return x; }
No *rotEsq(No *x) { No *y = x->dir; x->dir = y->esq; y->esq = x; atualiza(x); atualiza(y); return y; }

No *balanceia(No *n)
{
  atualiza(n);
  if (fb(n) > 1) {
    if (fb(n->esq) < 0) n->esq = rotEsq(n->esq);   // caso LR
    return rotDir(n);
  }
  if (fb(n) < -1) {
    if (fb(n->dir) > 0) n->dir = rotDir(n->dir);   // caso RL
    return rotEsq(n);
  }
  return n;
}

No *insere(No *r, int k)
{
  if (!r) return new No{k, 1, nullptr, nullptr};
  if (k < r->chave) r->esq = insere(r->esq, k);
  else if (k > r->chave) r->dir = insere(r->dir, k);
  else return r;
  return balanceia(r);
}

No *remove(No *r, int k)
{
  if (!r) return nullptr;
  if (k < r->chave) r->esq = remove(r->esq, k);
  else if (k > r->chave) r->dir = remove(r->dir, k);
  else if (r->esq && r->dir) {
    No *suc = r->dir;
    while (suc->esq) suc = suc->esq;
    r->chave = suc->chave;               // copia o sucessor
    r->dir = remove(r->dir, suc->chave); // e remove ele da subarvore direita
  } else {
    No *filho = r->esq ? r->esq : r->dir;
    delete r;
    return filho;                         // filho ja e AVL
  }
  return balanceia(r);
}

void desenha(No *r, int nivel = 0)
{
  if (!r) return;
  desenha(r->dir, nivel + 1);
  for (int i = 0; i < nivel; i++) cout << "      ";
  cout << r->chave << "(" << fb(r) << ")" << endl;
  desenha(r->esq, nivel + 1);
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *r = nullptr;
  int v[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 1};
  for (int x : v) r = insere(r, x);
  cout << "Arvore inicial:" << endl; desenha(r);

  r = remove(r, 80);   // desbalanceia o 75 e depois a raiz: duas rotacoes
  cout << "\nApos remover 80:" << endl; desenha(r);

  r = remove(r, 25);   // no com dois filhos
  cout << "\nApos remover 25:" << endl; desenha(r);
  libera(r);
  return 0;
}
