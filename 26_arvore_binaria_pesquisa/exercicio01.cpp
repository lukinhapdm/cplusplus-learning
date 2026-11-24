/*
Exercicio 1. Verificar se uma arvore binaria e uma ABB. Cuidado: nao basta comparar cada no com
seus filhos; todas as chaves da subarvore precisam respeitar os limites herdados dos ancestrais.
*/
#include <iostream>
#include <climits>
using namespace std;

struct No { int chave; No *esq, *dir; };

No *novo(int k, No *e = nullptr, No *d = nullptr) { return new No{k, e, d}; }

// cada no deve estar no intervalo (min, max) definido pelo caminho ate ele
bool ehABB(No *r, long min, long max)
{
  if (!r) return true;
  if (r->chave <= min || r->chave >= max) return false;
  return ehABB(r->esq, min, r->chave) && ehABB(r->dir, r->chave, max);
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  /*
         50                 50
       /    \             /    \
     30      70         30      70
    /  \               /  \
   20  40             20  60   <- 60 > 50 mas esta a esquerda de 50
  */
  No *a = novo(50, novo(30, novo(20), novo(40)), novo(70));
  No *b = novo(50, novo(30, novo(20), novo(60)), novo(70));
  cout << "Arvore A: " << (ehABB(a, LONG_MIN, LONG_MAX) ? "e ABB" : "nao e ABB") << endl;
  cout << "Arvore B: " << (ehABB(b, LONG_MIN, LONG_MAX) ? "e ABB" : "nao e ABB") << endl;
  libera(a); libera(b);
  return 0;
}
