/*
Exercicio 3. Contar as folhas (nos sem filhos) e somar todos os valores da arvore.
*/
#include <iostream>
using namespace std;

// Arvore binaria de busca: esquerda < no < direita
struct No { int valor; No *esq, *dir; };

No *insere(No *r, int x)
{
  if (r == nullptr) { No *n = new No; n->valor = x; n->esq = n->dir = nullptr; return n; }
  if (x < r->valor) r->esq = insere(r->esq, x);   // menor vai para a esquerda
  else r->dir = insere(r->dir, x);                // maior ou igual vai para a direita
  return r;
}

void emOrdem(No *r) { if (r) { emOrdem(r->esq); cout << r->valor << " "; emOrdem(r->dir); } }
void preOrdem(No *r) { if (r) { cout << r->valor << " "; preOrdem(r->esq); preOrdem(r->dir); } }
void posOrdem(No *r) { if (r) { posOrdem(r->esq); posOrdem(r->dir); cout << r->valor << " "; } }

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int folhas(No *r)
{
  if (r == nullptr) return 0;
  if (r->esq == nullptr && r->dir == nullptr) return 1;   // e folha
  return folhas(r->esq) + folhas(r->dir);
}

int soma(No *r) { return r ? r->valor + soma(r->esq) + soma(r->dir) : 0; }

int main()
{
  No *raiz = nullptr;
  int v[] = {8, 3, 10, 1, 6, 14, 4, 7};
  for (int x : v) raiz = insere(raiz, x);
  cout << "Folhas: " << folhas(raiz) << " | Soma: " << soma(raiz) << endl;
  libera(raiz);
  return 0;
}
