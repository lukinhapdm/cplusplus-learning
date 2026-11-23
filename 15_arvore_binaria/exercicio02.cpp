/*
Exercicio 2. Encontrar o menor e o maior valor da arvore binaria de busca.
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

// menor fica no extremo esquerdo, maior no extremo direito
int menor(No *r) { while (r->esq) r = r->esq; return r->valor; }
int maior(No *r) { while (r->dir) r = r->dir; return r->valor; }

int main()
{
  No *raiz = nullptr; int x;
  cout << "Digite 7 valores: ";
  for (int i = 0; i < 7; i++) { cin >> x; raiz = insere(raiz, x); }
  cout << "Menor: " << menor(raiz) << " | Maior: " << maior(raiz) << endl;
  libera(raiz);
  return 0;
}
