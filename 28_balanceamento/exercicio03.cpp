/*
Exercicio 3. Balanceamento periodico: criar uma classe ABB que, ao inserir, verifica se a altura passou
de 2 * floor(log2 n) + 1 e, nesse caso, executa o DSW. Inserir 1..100 em ordem e mostrar quando balanceou.
*/
#include <iostream>
using namespace std;

struct No { int chave; No *esq, *dir; };

class ABBAutoBalanceada {
  No *raiz = nullptr;
  int n = 0;

  static void rotDir(No *pai) { No *x = pai->dir, *e = x->esq; x->esq = e->dir; e->dir = x; pai->dir = e; }
  static void rotEsq(No *pai) { No *x = pai->dir, *d = x->dir; x->dir = d->esq; d->esq = x; pai->dir = d; }
  static void comprime(No *p, int k) { for (int i = 0; i < k; i++) { rotEsq(p); p = p->dir; } }
  static int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
  static void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

  void dsw()
  {
    No pseudo{0, nullptr, raiz};
    for (No *p = &pseudo; p->dir;) { if (p->dir->esq) rotDir(p); else p = p->dir; }
    int m = 1;
    while (m <= n + 1) m *= 2;
    m = m / 2 - 1;
    comprime(&pseudo, n - m);
    while (m > 1) { m /= 2; comprime(&pseudo, m); }
    raiz = pseudo.dir;
  }

public:
  ~ABBAutoBalanceada() { libera(raiz); }
  int altura() const { return altura(raiz); }

  void insere(int k)
  {
    No **p = &raiz;
    while (*p) {
      if (k == (*p)->chave) return;
      p = k < (*p)->chave ? &(*p)->esq : &(*p)->dir;
    }
    *p = new No{k, nullptr, nullptr};
    n++;
    int log = 0;
    while ((1 << (log + 1)) <= n) log++;
    if (altura() > 2 * log + 1) {   // ficou alta demais: balanceia
      int antes = altura();
      dsw();
      cout << "n = " << n << ": altura " << antes << " -> " << altura() << endl;
    }
  }
};

int main()
{
  ABBAutoBalanceada a;
  for (int k = 1; k <= 100; k++) a.insere(k);
  cout << "Altura final: " << a.altura() << endl;
  return 0;
}
