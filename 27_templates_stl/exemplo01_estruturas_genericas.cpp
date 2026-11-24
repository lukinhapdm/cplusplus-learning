/*
Exemplo 1. Estruturas de dados genericas com templates: a mesma Pilha e a mesma funcao de busca
funcionam para qualquer tipo T (int, double, string, structs com operador ==, ...).
O compilador gera uma versao do codigo para cada tipo usado (instanciacao).
*/
#include <iostream>
#include <string>
using namespace std;

// template de funcao: pesquisa sequencial para qualquer tipo que tenha ==
template <typename T>
int buscaSequencial(const T v[], int n, const T &chave)
{
  for (int i = 0; i < n; i++) if (v[i] == chave) return i;
  return -1;
}

// template de classe: pilha encadeada generica
template <typename T>
class Pilha {
  struct No { T valor; No *prox; };
  No *topo = nullptr;
  int n = 0;
public:
  ~Pilha() { while (!vazia()) desempilha(); }
  bool vazia() const { return topo == nullptr; }
  int tamanho() const { return n; }
  void empilha(const T &x) { topo = new No{x, topo}; n++; }
  T desempilha()
  {
    No *a = topo;
    T x = a->valor;
    topo = a->prox; delete a; n--;
    return x;
  }
  const T &consulta() const { return topo->valor; }
};

// template com parametro que nao e tipo: tamanho fixo conhecido em tempo de compilacao
template <typename T, int TAM>
class VetorFixo {
  T dados[TAM];
public:
  T &operator[](int i) { return dados[i]; }
  int tamanho() const { return TAM; }
};

int main()
{
  int vi[] = {4, 8, 15, 16, 23, 42};
  string vs[] = {"ana", "bia", "caio"};
  cout << "23 na posicao " << buscaSequencial(vi, 6, 23) << endl;
  cout << "bia na posicao " << buscaSequencial(vs, 3, string("bia")) << endl;

  Pilha<string> p;
  p.empilha("primeiro"); p.empilha("segundo"); p.empilha("terceiro");
  cout << "Pilha com " << p.tamanho() << " elementos: ";
  while (!p.vazia()) cout << p.desempilha() << " ";
  cout << endl;

  Pilha<double> pd;
  pd.empilha(3.14); pd.empilha(2.71);
  cout << "Topo da pilha de double: " << pd.consulta() << endl;

  VetorFixo<char, 5> vf;
  for (int i = 0; i < vf.tamanho(); i++) vf[i] = 'a' + i;
  for (int i = 0; i < vf.tamanho(); i++) cout << vf[i];
  cout << endl;
  return 0;
}
