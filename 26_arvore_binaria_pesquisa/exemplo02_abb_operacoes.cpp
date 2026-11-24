/*
Exemplo 2. Outras operacoes em ABB: minimo, maximo, sucessor, predecessor, altura, numero de nos
e k-esimo menor. Mostra tambem que a ordem de insercao define a forma (e a altura) da arvore.
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

No *minimo(No *r) { while (r && r->esq) r = r->esq; return r; }
No *maximo(No *r) { while (r && r->dir) r = r->dir; return r; }

// sucessor de k: menor chave maior que k (desce a partir da raiz lembrando o ultimo "desvio a esquerda")
No *sucessor(No *r, int k)
{
  No *suc = nullptr;
  while (r) {
    if (k < r->chave) { suc = r; r = r->esq; }
    else r = r->dir;
  }
  return suc;
}

No *predecessor(No *r, int k)
{
  No *pred = nullptr;
  while (r) {
    if (k > r->chave) { pred = r; r = r->dir; }
    else r = r->esq;
  }
  return pred;
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
int contaNos(No *r) { return r ? 1 + contaNos(r->esq) + contaNos(r->dir) : 0; }

// k-esimo menor: percurso em ordem parando na k-esima visita
No *kEsimo(No *r, int &k)
{
  if (!r) return nullptr;
  No *e = kEsimo(r->esq, k);
  if (e) return e;
  if (--k == 0) return r;
  return kEsimo(r->dir, k);
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *r = nullptr;
  int v[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
  for (int x : v) r = insere(r, x);

  cout << "Minimo: " << minimo(r)->chave << ", maximo: " << maximo(r)->chave << endl;
  cout << "Sucessor de 45: " << sucessor(r, 45)->chave << ", predecessor de 60: " << predecessor(r, 60)->chave << endl;
  cout << "Nos: " << contaNos(r) << ", altura: " << altura(r) << endl;
  for (int k = 1; k <= 3; k++) { int c = k; cout << k << "o menor: " << kEsimo(r, c)->chave << endl; }

  No *degenerada = nullptr;   // insercao em ordem crescente vira uma lista
  for (int x = 1; x <= 9; x++) degenerada = insere(degenerada, x);
  cout << "Mesmas 9 chaves em ordem crescente: altura " << altura(degenerada) << endl;

  libera(r); libera(degenerada);
  return 0;
}
