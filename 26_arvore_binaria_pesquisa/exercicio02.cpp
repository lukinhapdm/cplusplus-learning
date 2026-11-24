/*
Exercicio 2. Imprimir em ordem crescente apenas as chaves de uma ABB que estao no intervalo [a, b],
sem visitar subarvores que certamente estao fora do intervalo.
*/
#include <iostream>
using namespace std;

struct No { int chave; No *esq, *dir; };

No *insere(No *r, int k)
{
  if (!r) return new No{k, nullptr, nullptr};
  if (k < r->chave) r->esq = insere(r->esq, k);
  else if (k > r->chave) r->dir = insere(r->dir, k);
  return r;
}

void intervalo(No *r, int a, int b, int &visitados)
{
  if (!r) return;
  visitados++;
  if (r->chave > a) intervalo(r->esq, a, b, visitados);   // so desce a esquerda se pode haver chaves >= a
  if (r->chave >= a && r->chave <= b) cout << r->chave << " ";
  if (r->chave < b) intervalo(r->dir, a, b, visitados);   // so desce a direita se pode haver chaves <= b
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *r = nullptr;
  int v[] = {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93};
  for (int x : v) r = insere(r, x);
  int vis = 0;
  cout << "Chaves em [30, 60]: ";
  intervalo(r, 30, 60, vis);
  cout << "\nNos visitados: " << vis << " de 15" << endl;
  libera(r);
  return 0;
}
