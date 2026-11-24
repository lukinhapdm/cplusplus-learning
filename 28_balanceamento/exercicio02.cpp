/*
Exercicio 2. Instrumentar o DSW para contar as rotacoes de cada fase. Testar com arvores de n = 7, 15, 100 e 1000
nos inseridos em ordem crescente (ja sao espinhas: fase 1 sem rotacoes) e em ordem decrescente
(fase 1 com n - 1 rotacoes). Conferir que o total e sempre O(n).
*/
#include <iostream>
using namespace std;

struct No { int chave; No *esq, *dir; };

int rotacoes = 0;

void rotDirFilho(No *pai) { No *n = pai->dir, *e = n->esq; n->esq = e->dir; e->dir = n; pai->dir = e; rotacoes++; }
void rotEsqFilho(No *pai) { No *n = pai->dir, *d = n->dir; n->dir = d->esq; d->esq = n; pai->dir = d; rotacoes++; }

int criaEspinha(No *pseudo)
{
  int n = 0;
  for (No *pai = pseudo; pai->dir;) {
    if (pai->dir->esq) rotDirFilho(pai);
    else { pai = pai->dir; n++; }
  }
  return n;
}

void comprime(No *pseudo, int vezes) { No *pai = pseudo; for (int i = 0; i < vezes; i++) { rotEsqFilho(pai); pai = pai->dir; } }

No *dsw(No *raiz, int &fase1, int &fase2)
{
  No pseudo{0, nullptr, raiz};
  rotacoes = 0;
  int n = criaEspinha(&pseudo);
  fase1 = rotacoes;
  int m = 1;
  while (m <= n + 1) m *= 2;
  m = m / 2 - 1;
  comprime(&pseudo, n - m);
  while (m > 1) { m /= 2; comprime(&pseudo, m); }
  fase2 = rotacoes - fase1;
  return pseudo.dir;
}

// cria direto a lista degenerada (insercao em ordem) sem recursao, para aguentar n grande
No *degenerada(int n, bool crescente)
{
  No *r = nullptr;
  for (int i = n; i >= 1; i--) {
    if (crescente) r = new No{i, nullptr, r};   // so filhos a direita
    else r = new No{n - i + 1, r, nullptr};     // so filhos a esquerda
  }
  return r;
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  for (int n : {7, 15, 100, 1000}) {
    for (bool cresc : {true, false}) {
      int f1, f2;
      No *r = dsw(degenerada(n, cresc), f1, f2);
      cout << "n = " << n << (cresc ? " crescente:   " : " decrescente: ") << "fase 1 = " << f1
           << ", fase 2 = " << f2 << ", altura final = " << altura(r) << endl;
      libera(r);
    }
  }
  return 0;
}
