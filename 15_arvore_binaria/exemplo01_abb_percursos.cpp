/*
Exemplo 1. Arvore binaria de busca: insercao e percursos em-ordem, pre-ordem e pos-ordem.
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

int main()
{
  No *raiz = nullptr;
  int v[] = {50, 30, 70, 20, 40, 60, 80};
  for (int x : v) raiz = insere(raiz, x);
  cout << "Em ordem:  "; emOrdem(raiz); cout << endl;    // sai ordenado
  cout << "Pre ordem: "; preOrdem(raiz); cout << endl;
  cout << "Pos ordem: "; posOrdem(raiz); cout << endl;
  libera(raiz);
  return 0;
}
