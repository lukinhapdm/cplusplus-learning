/*
Exercicio 3. Guardar o fator de balanceamento em cada no (em vez da altura), como no algoritmo original:
na insercao, uma variavel "cresceu" indica se a subarvore aumentou de altura. Ao receber cresceu = true
de um filho, o no ajusta seu fb: se ficou 0, para; se ficou +-1, continua subindo; se ficou +-2, rotaciona.
*/
#include <iostream>
using namespace std;

struct No { int chave, fb; No *esq, *dir; };   // fb = altura(esq) - altura(dir)

// rotacao simples/dupla quando o lado esquerdo ficou com fb = +2
No *corrigeEsq(No *p)
{
  No *u = p->esq;
  if (u->fb == 1) {               // LL
    p->esq = u->dir; u->dir = p;
    p->fb = u->fb = 0;
    return u;
  }
  No *v = u->dir;                 // LR
  u->dir = v->esq; v->esq = u;
  p->esq = v->dir; v->dir = p;
  p->fb = (v->fb == 1) ? -1 : 0;
  u->fb = (v->fb == -1) ? 1 : 0;
  v->fb = 0;
  return v;
}

No *corrigeDir(No *p)
{
  No *u = p->dir;
  if (u->fb == -1) {              // RR
    p->dir = u->esq; u->esq = p;
    p->fb = u->fb = 0;
    return u;
  }
  No *v = u->esq;                 // RL
  u->esq = v->dir; v->dir = u;
  p->dir = v->esq; v->esq = p;
  p->fb = (v->fb == -1) ? 1 : 0;
  u->fb = (v->fb == 1) ? -1 : 0;
  v->fb = 0;
  return v;
}

No *insere(No *p, int k, bool &cresceu)
{
  if (!p) { cresceu = true; return new No{k, 0, nullptr, nullptr}; }
  if (k == p->chave) { cresceu = false; return p; }
  if (k < p->chave) {
    p->esq = insere(p->esq, k, cresceu);
    if (cresceu) {
      p->fb++;
      if (p->fb == 0) cresceu = false;                       // equilibrou
      else if (p->fb == 2) { p = corrigeEsq(p); cresceu = false; }
    }
  } else {
    p->dir = insere(p->dir, k, cresceu);
    if (cresceu) {
      p->fb--;
      if (p->fb == 0) cresceu = false;
      else if (p->fb == -2) { p = corrigeDir(p); cresceu = false; }
    }
  }
  return p;
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }

// confere se o fb guardado bate com o fb real calculado pelas alturas
bool confere(No *r)
{
  if (!r) return true;
  int real = altura(r->esq) - altura(r->dir);
  return real == r->fb && real >= -1 && real <= 1 && confere(r->esq) && confere(r->dir);
}

void desenha(No *r, int nivel = 0)
{
  if (!r) return;
  desenha(r->dir, nivel + 1);
  for (int i = 0; i < nivel; i++) cout << "      ";
  cout << r->chave << "(" << r->fb << ")" << endl;
  desenha(r->esq, nivel + 1);
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *r = nullptr;
  bool c;
  int v[] = {40, 20, 60, 10, 30, 25, 50, 70, 80, 75, 5, 1};
  for (int x : v) r = insere(r, x, c);
  desenha(r);
  cout << "fb guardados corretos: " << (confere(r) ? "sim" : "nao") << endl;
  libera(r);
  return 0;
}
