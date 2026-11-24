/*
Exercicio 1. Escrever duas funcoes de verificacao:
(a) balanceadaAltura: para todo no, as alturas das subarvores diferem de no maximo 1;
(b) alturaMinima: a altura da arvore e floor(log2 n) + 1.
Testar em uma ABB aleatoria antes e depois de balancear com a tecnica da busca binaria.
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct No { int chave; No *esq, *dir; };

No *insere(No *r, int k)
{
  if (!r) return new No{k, nullptr, nullptr};
  if (k < r->chave) r->esq = insere(r->esq, k);
  else if (k > r->chave) r->dir = insere(r->dir, k);
  return r;
}

int altura(No *r) { if (!r) return 0; int e = altura(r->esq), d = altura(r->dir); return 1 + (e > d ? e : d); }
int contaNos(No *r) { return r ? 1 + contaNos(r->esq) + contaNos(r->dir) : 0; }

// devolve a altura, ou -1 se encontrar algum no desbalanceado (evita recalcular alturas)
int verifica(No *r)
{
  if (!r) return 0;
  int e = verifica(r->esq), d = verifica(r->dir);
  if (e < 0 || d < 0 || abs(e - d) > 1) return -1;
  return 1 + (e > d ? e : d);
}
bool balanceadaAltura(No *r) { return verifica(r) >= 0; }

bool alturaMinima(No *r)
{
  int n = contaNos(r), log = 0;
  while ((1 << (log + 1)) <= n) log++;   // log = floor(log2 n)
  return altura(r) == log + 1;
}

void paraVetor(No *r, vector<int> &v) { if (r) { paraVetor(r->esq, v); v.push_back(r->chave); paraVetor(r->dir, v); } }
No *constroi(const vector<int> &v, int e, int d)
{
  if (e > d) return nullptr;
  int m = (e + d) / 2;
  return new No{v[m], constroi(v, e, m - 1), constroi(v, m + 1, d)};
}
void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

void relatorio(const char *titulo, No *r)
{
  cout << titulo << ": n = " << contaNos(r) << ", altura = " << altura(r)
       << ", balanceada = " << (balanceadaAltura(r) ? "sim" : "nao")
       << ", altura minima = " << (alturaMinima(r) ? "sim" : "nao") << endl;
}

int main()
{
  srand(7);
  No *r = nullptr;
  for (int i = 0; i < 50; i++) r = insere(r, rand() % 1000);
  relatorio("Aleatoria", r);
  vector<int> v; paraVetor(r, v); libera(r);
  r = constroi(v, 0, (int)v.size() - 1);
  relatorio("Balanceada", r);
  libera(r);
  return 0;
}
