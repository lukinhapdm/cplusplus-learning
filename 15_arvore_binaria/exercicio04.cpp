/*
Exercicio 4. Ler palavras e guarda-las em uma arvore binaria de busca de strings; mostrar em ordem alfabetica.
*/
#include <iostream>
#include <string>
using namespace std;

struct No { string palavra; No *esq, *dir; };

No *insere(No *r, string p)
{
  if (!r) return new No{p, nullptr, nullptr};
  if (p < r->palavra) r->esq = insere(r->esq, p);   // string compara em ordem alfabetica
  else r->dir = insere(r->dir, p);
  return r;
}

void emOrdem(No *r) { if (r) { emOrdem(r->esq); cout << r->palavra << endl; emOrdem(r->dir); } }
void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  No *raiz = nullptr; string p;
  cout << "Palavras (fim para parar): ";
  while (cin >> p && p != "fim") raiz = insere(raiz, p);
  emOrdem(raiz);
  libera(raiz);
  return 0;
}
