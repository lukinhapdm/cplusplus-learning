/*
Exercicio 1. Transformar a ABB em um template de classe ABB<T> e usa-la com int e com string.
O tipo T precisa ter o operador <.
*/
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ABB {
  struct No { T chave; No *esq, *dir; };
  No *raiz = nullptr;

  No *insere(No *r, const T &k)
  {
    if (!r) return new No{k, nullptr, nullptr};
    if (k < r->chave) r->esq = insere(r->esq, k);
    else if (r->chave < k) r->dir = insere(r->dir, k);   // so usa <
    return r;
  }
  void emOrdem(No *r) const { if (r) { emOrdem(r->esq); cout << r->chave << " "; emOrdem(r->dir); } }
  void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

public:
  ~ABB() { libera(raiz); }
  void insere(const T &k) { raiz = insere(raiz, k); }
  bool busca(const T &k) const
  {
    No *a = raiz;
    while (a) {
      if (k < a->chave) a = a->esq;
      else if (a->chave < k) a = a->dir;
      else return true;
    }
    return false;
  }
  void imprime() const { emOrdem(raiz); cout << endl; }
};

int main()
{
  ABB<int> ai;
  for (int x : {30, 10, 50, 20, 40}) ai.insere(x);
  ai.imprime();
  cout << "20? " << ai.busca(20) << "  25? " << ai.busca(25) << endl;

  ABB<string> as;
  for (string s : {"maria", "joao", "zeca", "ana", "pedro"}) as.insere(s);
  as.imprime();
  cout << "zeca? " << as.busca("zeca") << endl;
  return 0;
}
