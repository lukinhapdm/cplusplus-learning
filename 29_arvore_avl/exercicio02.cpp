/*
Exercicio 2. Arvores de Fibonacci: a AVL de altura h com o menor numero possivel de nos tem
N(h) = N(h-1) + N(h-2) + 1 nos (N(0) = 0, N(1) = 1). Construir essa arvore para h = 1..6,
verificar que ela e AVL e comparar N(h) com 2^h - 1 (arvore cheia).
Daqui vem o limite: altura de uma AVL com n nos < 1.44 log2(n + 2).
*/
#include <iostream>
#include <cstdlib>
using namespace std;

struct No { int chave; No *esq, *dir; };

// raiz com subarvore esquerda de altura h-1 e direita de altura h-2 (as duas minimas)
No *fibonacci(int h, int &proxChave)
{
  if (h <= 0) return nullptr;
  No *n = new No{0, nullptr, nullptr};
  n->esq = fibonacci(h - 1, proxChave);
  n->chave = proxChave++;   // numera em ordem para que seja ABB
  n->dir = fibonacci(h - 2, proxChave);
  return n;
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
int contaNos(No *r) { return r ? 1 + contaNos(r->esq) + contaNos(r->dir) : 0; }
bool ehAVL(No *r) { return !r || (abs(altura(r->esq) - altura(r->dir)) <= 1 && ehAVL(r->esq) && ehAVL(r->dir)); }
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
  for (int h = 1; h <= 6; h++) {
    int c = 1;
    No *r = fibonacci(h, c);
    cout << "h = " << h << ": N(h) = " << contaNos(r) << ", cheia = " << (1 << h) - 1
         << ", altura = " << altura(r) << ", AVL = " << (ehAVL(r) ? "sim" : "nao") << endl;
    if (h == 4) desenha(r);
    libera(r);
  }
  return 0;
}
