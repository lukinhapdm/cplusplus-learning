/*
Exercicio 1. Funcoes recursivas para contar os nos e calcular a altura da arvore.
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

int contaNos(No *r) { return r ? 1 + contaNos(r->esq) + contaNos(r->dir) : 0; }

// altura = maior caminho da raiz ate uma folha
int altura(No *r)
{
  if (r == nullptr) return -1;
  int he = altura(r->esq), hd = altura(r->dir);
  return 1 + (he > hd ? he : hd);
}

int main()
{
  No *raiz = nullptr;
  int v[] = {8, 3, 10, 1, 6, 14, 4, 7};
  for (int x : v) raiz = insere(raiz, x);
  cout << "Nos: " << contaNos(raiz) << " | Altura: " << altura(raiz) << endl;
  libera(raiz);
  return 0;
}
