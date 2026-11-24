/*
Exemplo 1. Balanceamento de ABB pela tecnica baseada em busca binaria.
1) Percorre a arvore em ordem e copia as chaves para um vetor (que fica ordenado).
2) Reconstroi a arvore inserindo primeiro o elemento do meio do vetor e depois, recursivamente,
   o meio da metade esquerda e o meio da metade direita (a mesma divisao da pesquisa binaria).
Resultado: arvore com altura minima, floor(log2 n) + 1. Custo O(n), mas precisa de vetor auxiliar.
*/
#include <iostream>
#include <vector>
using namespace std;

struct No { int chave; No *esq, *dir; };

No *insere(No *r, int k)
{
  if (!r) return new No{k, nullptr, nullptr};
  if (k < r->chave) r->esq = insere(r->esq, k);
  else if (k > r->chave) r->dir = insere(r->dir, k);
  return r;
}

void paraVetor(No *r, vector<int> &v)
{
  if (!r) return;
  paraVetor(r->esq, v);
  v.push_back(r->chave);
  paraVetor(r->dir, v);
}

// constroi a arvore balanceada com as chaves v[esq..dir]
No *constroi(const vector<int> &v, int esq, int dir)
{
  if (esq > dir) return nullptr;
  int meio = (esq + dir) / 2;
  No *n = new No{v[meio], nullptr, nullptr};
  n->esq = constroi(v, esq, meio - 1);
  n->dir = constroi(v, meio + 1, dir);
  return n;
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

No *balanceia(No *r)
{
  vector<int> v;
  paraVetor(r, v);
  libera(r);
  return constroi(v, 0, (int)v.size() - 1);
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }

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
  No *r = nullptr;
  for (int k = 1; k <= 10; k++) r = insere(r, k * 10);   // insercao ordenada: arvore degenerada
  cout << "Antes: altura " << altura(r) << endl;
  r = balanceia(r);
  cout << "Depois: altura " << altura(r) << endl;
  desenha(r);
  libera(r);
  return 0;
}
