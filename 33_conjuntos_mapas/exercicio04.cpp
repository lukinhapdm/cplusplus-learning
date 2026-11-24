/*
Exercicio 4. Implementar um mapa simples Mapa<K, V> com template sobre uma ABB, com as operacoes
insere (atualiza se a chave existir), busca (devolve ponteiro para o valor ou nullptr), remove e
um operador [] que cria a chave com valor padrao, como no map da STL.
*/
#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V>
class Mapa {
  struct No { K chave; V valor; No *esq, *dir; };
  No *raiz = nullptr;
  int n = 0;

  No **procura(const K &k)   // devolve o endereco do ponteiro onde a chave esta (ou deveria estar)
  {
    No **p = &raiz;
    while (*p && (*p)->chave != k) p = k < (*p)->chave ? &(*p)->esq : &(*p)->dir;
    return p;
  }
  void emOrdem(No *r) const { if (r) { emOrdem(r->esq); cout << r->chave << " -> " << r->valor << endl; emOrdem(r->dir); } }
  void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

public:
  ~Mapa() { libera(raiz); }
  int tamanho() const { return n; }

  void insere(const K &k, const V &v)
  {
    No **p = procura(k);
    if (*p) (*p)->valor = v;
    else { *p = new No{k, v, nullptr, nullptr}; n++; }
  }

  V *busca(const K &k) { No **p = procura(k); return *p ? &(*p)->valor : nullptr; }

  V &operator[](const K &k)
  {
    No **p = procura(k);
    if (!*p) { *p = new No{k, V(), nullptr, nullptr}; n++; }
    return (*p)->valor;
  }

  bool remove(const K &k)
  {
    No **p = procura(k);
    No *a = *p;
    if (!a) return false;
    if (a->esq && a->dir) {   // dois filhos: traz o sucessor
      No **s = &a->dir;
      while ((*s)->esq) s = &(*s)->esq;
      No *suc = *s;
      a->chave = suc->chave; a->valor = suc->valor;
      *s = suc->dir;
      delete suc;
    } else {
      *p = a->esq ? a->esq : a->dir;
      delete a;
    }
    n--;
    return true;
  }

  void imprime() const { emOrdem(raiz); }
};

int main()
{
  Mapa<string, double> precos;
  precos.insere("cafe", 18.9);
  precos.insere("arroz", 25.5);
  precos.insere("feijao", 9.8);
  precos["leite"] = 5.49;
  precos["cafe"] = 19.9;   // atualiza
  precos.imprime();

  double *p = precos.busca("arroz");
  if (p) cout << "arroz custa " << *p << endl;
  precos.remove("cafe");
  cout << "Apos remover cafe (" << precos.tamanho() << " itens):" << endl;
  precos.imprime();

  Mapa<char, int> contagem;
  for (char c : string("banana")) contagem[c]++;
  contagem.imprime();
  return 0;
}
