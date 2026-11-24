/*
Exemplo 1. Arvore Binaria de Pesquisa (ABB) como classe. Para todo no: chaves da subarvore esquerda
sao menores e as da direita sao maiores. Busca, insercao e remocao custam O(altura).
Remocao: (1) folha: apaga; (2) um filho: o filho sobe; (3) dois filhos: troca pelo sucessor
(menor chave da subarvore direita) e remove o sucessor.
*/
#include <iostream>
using namespace std;

struct No { int chave; No *esq, *dir; };

class ABB {
  No *raiz = nullptr;

  No *insere(No *r, int k)
  {
    if (!r) return new No{k, nullptr, nullptr};
    if (k < r->chave) r->esq = insere(r->esq, k);
    else if (k > r->chave) r->dir = insere(r->dir, k);
    return r;   // chave repetida e ignorada
  }

  No *remove(No *r, int k)
  {
    if (!r) return nullptr;
    if (k < r->chave) r->esq = remove(r->esq, k);
    else if (k > r->chave) r->dir = remove(r->dir, k);
    else if (r->esq && r->dir) {
      No *suc = r->dir;
      while (suc->esq) suc = suc->esq;   // sucessor: mais a esquerda da subarvore direita
      r->chave = suc->chave;
      r->dir = remove(r->dir, suc->chave);
    } else {
      No *filho = r->esq ? r->esq : r->dir;   // zero ou um filho
      delete r;
      return filho;
    }
    return r;
  }

  void emOrdem(No *r) { if (r) { emOrdem(r->esq); cout << r->chave << " "; emOrdem(r->dir); } }
  void preOrdem(No *r) { if (r) { cout << r->chave << " "; preOrdem(r->esq); preOrdem(r->dir); } }
  void posOrdem(No *r) { if (r) { posOrdem(r->esq); posOrdem(r->dir); cout << r->chave << " "; } }
  void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

  // imprime "deitada": raiz a esquerda, subarvore direita em cima
  void desenha(No *r, int nivel)
  {
    if (!r) return;
    desenha(r->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "    ";
    cout << r->chave << endl;
    desenha(r->esq, nivel + 1);
  }

public:
  ~ABB() { libera(raiz); }
  void insere(int k) { raiz = insere(raiz, k); }
  void remove(int k) { raiz = remove(raiz, k); }

  bool busca(int k)
  {
    No *a = raiz;
    while (a && a->chave != k) a = k < a->chave ? a->esq : a->dir;
    return a != nullptr;
  }

  void percursos()
  {
    cout << "Em ordem:  "; emOrdem(raiz); cout << endl;
    cout << "Pre-ordem: "; preOrdem(raiz); cout << endl;
    cout << "Pos-ordem: "; posOrdem(raiz); cout << endl;
  }
  void desenha() { desenha(raiz, 0); }
};

int main()
{
  ABB a;
  int v[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
  for (int x : v) a.insere(x);
  a.desenha();
  a.percursos();
  cout << "Busca 45: " << (a.busca(45) ? "achou" : "nao achou") << endl;

  a.remove(20);   // folha
  a.remove(60);   // um filho
  a.remove(30);   // dois filhos
  cout << "\nApos remover 20, 60 e 30:" << endl;
  a.desenha();
  a.percursos();
  return 0;
}
