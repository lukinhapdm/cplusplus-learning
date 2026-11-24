/*
Exemplo 2. Algoritmo DSW (Day, Stout e Warren): balanceia a ABB no lugar, so com rotacoes, sem vetor auxiliar.
Fase 1 (espinha dorsal): rotacoes a direita ate a arvore virar uma "lista" so com filhos a direita.
Fase 2 (compressao): m = 2^floor(log2(n+1)) - 1 (maior arvore completa que cabe em n nos).
  - faz n - m rotacoes a esquerda (nos impares da espinha) para sobrar exatamente m nos na espinha;
  - enquanto m > 1: m = m / 2 e faz m rotacoes a esquerda, um no sim, um nao.
Custo O(n) de tempo e O(1) de memoria extra.
*/
#include <iostream>
using namespace std;

struct No { int chave; No *esq, *dir; };

No *insere(No *r, int k)
{
  if (!r) return new No{k, nullptr, nullptr};
  if (k < r->chave) r->esq = insere(r->esq, k);
  else if (k > r->chave) r->dir = insere(r->dir, k);
  return r;
}

// rotacao a direita do filho direito de 'pai' (pai->dir = filho com filho esquerdo)
void rotDirFilho(No *pai)
{
  No *n = pai->dir, *e = n->esq;
  n->esq = e->dir;
  e->dir = n;
  pai->dir = e;
}

// rotacao a esquerda do filho direito de 'pai'
void rotEsqFilho(No *pai)
{
  No *n = pai->dir, *d = n->dir;
  n->dir = d->esq;
  d->esq = n;
  pai->dir = d;
}

// fase 1: transforma em espinha dorsal; devolve o numero de nos
int criaEspinha(No *pseudoRaiz)
{
  int n = 0;
  No *pai = pseudoRaiz;
  while (pai->dir) {
    if (pai->dir->esq) rotDirFilho(pai);   // ainda tem filho esquerdo: gira
    else { pai = pai->dir; n++; }          // nao tem: avanca na espinha
  }
  return n;
}

void comprime(No *pseudoRaiz, int vezes)
{
  No *pai = pseudoRaiz;
  for (int i = 0; i < vezes; i++) {
    rotEsqFilho(pai);
    pai = pai->dir;   // pula um no (rotaciona um sim, um nao)
  }
}

No *dsw(No *raiz)
{
  No pseudo{0, nullptr, raiz};   // pseudo-raiz: evita tratar a raiz como caso especial
  int n = criaEspinha(&pseudo);
  int m = 1;
  while (m <= n + 1) m *= 2;
  m = m / 2 - 1;                 // m = 2^floor(log2(n+1)) - 1
  comprime(&pseudo, n - m);
  while (m > 1) {
    m /= 2;
    comprime(&pseudo, m);
  }
  return pseudo.dir;
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

void desenha(No *r, int nivel = 0)
{
  if (!r) return;
  desenha(r->dir, nivel + 1);
  for (int i = 0; i < nivel; i++) cout << "    ";
  cout << r->chave << endl;
  desenha(r->esq, nivel + 1);
}

int main()
{
  No *r = nullptr;
  int v[] = {5, 10, 20, 15, 30, 25, 40, 23, 28, 35, 45, 50};
  for (int x : v) r = insere(r, x);
  cout << "Antes (altura " << altura(r) << "):" << endl;
  desenha(r);
  r = dsw(r);
  cout << "\nDepois do DSW (altura " << altura(r) << "):" << endl;
  desenha(r);
  libera(r);
  return 0;
}
