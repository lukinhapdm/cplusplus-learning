/*
Exercicio 3. Na arvore Patricia: (a) listar as chaves em ordem crescente (percurso esq -> dir das folhas);
(b) contar nos internos e externos e conferir que internos = externos - 1;
(c) listar todas as chaves cujo bit mais significativo (bit 1) e 1, sem visitar a subarvore do bit 0.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

const int D = 8;
struct No { bool externo; int indice, chave; No *esq, *dir; };

int bit(int i, int k) { return (k >> (D - i)) & 1; }

No *insereEntre(int k, No *t, int i)
{
  if (t->externo || i < t->indice) {
    No *p = new No{true, 0, k, nullptr, nullptr};
    return bit(i, k) ? new No{false, i, 0, t, p} : new No{false, i, 0, p, t};
  }
  if (bit(t->indice, k)) t->dir = insereEntre(k, t->dir, i);
  else t->esq = insereEntre(k, t->esq, i);
  return t;
}

No *insere(No *t, int k)
{
  if (!t) return new No{true, 0, k, nullptr, nullptr};
  No *p = t;
  while (!p->externo) p = bit(p->indice, k) ? p->dir : p->esq;
  int i = 1;
  while (i <= D && bit(i, k) == bit(i, p->chave)) i++;
  return i > D ? t : insereEntre(k, t, i);
}

// como o bit 0 vai para a esquerda, as folhas da esquerda para a direita estao em ordem crescente
void emOrdem(No *t) { if (!t) return; if (t->externo) { cout << t->chave << " "; return; } emOrdem(t->esq); emOrdem(t->dir); }

void conta(No *t, int &internos, int &externos)
{
  if (!t) return;
  if (t->externo) { externos++; return; }
  internos++;
  conta(t->esq, internos, externos);
  conta(t->dir, internos, externos);
}

// se a raiz testa o bit 1, a resposta e a subarvore direita inteira
void comBit1(No *t)
{
  if (!t) return;
  if (!t->externo && t->indice == 1) { emOrdem(t->dir); return; }
  // senao todas as chaves concordam no bit 1: basta testar uma folha
  No *f = t;
  while (!f->externo) f = f->esq;
  if (bit(1, f->chave)) emOrdem(t);
}

void libera(No *t) { if (t) { libera(t->esq); libera(t->dir); delete t; } }

int main()
{
  srand(3);
  No *t = nullptr;
  for (int i = 0; i < 15; i++) t = insere(t, rand() % 256);
  cout << "Em ordem: "; emOrdem(t); cout << endl;
  int in = 0, ex = 0;
  conta(t, in, ex);
  cout << "Internos: " << in << ", externos: " << ex << endl;
  cout << "Chaves >= 128 (bit 1 = 1): "; comBit1(t); cout << endl;
  libera(t);
  return 0;
}
