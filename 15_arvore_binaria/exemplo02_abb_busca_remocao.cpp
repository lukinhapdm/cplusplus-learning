/*
Exemplo 2. Busca e remocao na arvore binaria de busca.
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

bool busca(No *r, int x)
{
  while (r != nullptr) {
    if (x == r->valor) return true;
    r = (x < r->valor) ? r->esq : r->dir;   // desce para o lado certo
  }
  return false;
}

No *remove(No *r, int x)
{
  if (r == nullptr) return nullptr;
  if (x < r->valor) r->esq = remove(r->esq, x);
  else if (x > r->valor) r->dir = remove(r->dir, x);
  else {
    // caso 1 e 2: zero ou um filho
    if (r->esq == nullptr) { No *d = r->dir; delete r; return d; }
    if (r->dir == nullptr) { No *e = r->esq; delete r; return e; }
    // caso 3: dois filhos -> troca pelo menor da direita
    No *m = r->dir;
    while (m->esq) m = m->esq;
    r->valor = m->valor;
    r->dir = remove(r->dir, m->valor);
  }
  return r;
}

int main()
{
  No *raiz = nullptr;
  int v[] = {50, 30, 70, 20, 40, 60, 80};
  for (int x : v) raiz = insere(raiz, x);
  cout << "Tem 40? " << (busca(raiz, 40) ? "sim" : "nao") << endl;
  raiz = remove(raiz, 50);   // remove a raiz (dois filhos)
  emOrdem(raiz); cout << endl;
  libera(raiz);
  return 0;
}
