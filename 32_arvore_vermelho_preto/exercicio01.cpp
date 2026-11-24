/*
Exercicio 1. Escrever uma funcao que verifica as quatro propriedades de uma arvore vermelho-preto
(e tambem a propriedade de ABB) e devolve a altura negra. Testar com uma arvore correta, construida
pela insercao, e com arvores montadas a mao que violam cada regra.
*/
#include <iostream>
#include <climits>
using namespace std;

enum Cor { VERMELHO, PRETO };
struct No { int chave; Cor cor; No *esq, *dir; };

No *n(int k, Cor c, No *e = nullptr, No *d = nullptr) { return new No{k, c, e, d}; }

// devolve a altura negra da subarvore, ou -1 se alguma regra for violada (aqui nullptr = NIL preto)
int alturaNegra(No *r, long min, long max, const char *&erro)
{
  if (!r) return 1;   // NIL conta como preto
  if (r->chave <= min || r->chave >= max) { erro = "nao e ABB"; return -1; }
  if (r->cor == VERMELHO && ((r->esq && r->esq->cor == VERMELHO) || (r->dir && r->dir->cor == VERMELHO))) {
    erro = "vermelho com filho vermelho"; return -1;
  }
  int e = alturaNegra(r->esq, min, r->chave, erro);
  int d = alturaNegra(r->dir, r->chave, max, erro);
  if (e < 0 || d < 0) return -1;
  if (e != d) { erro = "alturas negras diferentes"; return -1; }
  return e + (r->cor == PRETO ? 1 : 0);
}

void verifica(const char *nome, No *r)
{
  const char *erro = "";
  if (r && r->cor != PRETO) { cout << nome << ": invalida (raiz vermelha)" << endl; return; }
  int h = alturaNegra(r, LONG_MIN, LONG_MAX, erro);
  if (h < 0) cout << nome << ": invalida (" << erro << ")" << endl;
  else cout << nome << ": valida, altura negra = " << h << endl;
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *ok = n(20, PRETO, n(10, PRETO, n(5, VERMELHO), n(15, VERMELHO)), n(30, PRETO));
  No *raizV = n(20, VERMELHO, n(10, PRETO), n(30, PRETO));
  No *duasV = n(20, PRETO, n(10, VERMELHO, n(5, VERMELHO)), n(30, VERMELHO));
  No *negra = n(20, PRETO, n(10, PRETO, n(5, PRETO)), n(30, PRETO));
  No *naoABB = n(20, PRETO, n(10, PRETO, nullptr, n(25, VERMELHO)), n(30, PRETO));
  verifica("ok", ok); verifica("raizV", raizV); verifica("duasV", duasV);
  verifica("negra", negra); verifica("naoABB", naoABB);
  for (No *r : {ok, raizV, duasV, negra, naoABB}) libera(r);
  return 0;
}
