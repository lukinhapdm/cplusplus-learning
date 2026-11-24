/*
Exemplo 1. Conjuntos (TAD Conjunto): colecao sem elementos repetidos com operacoes de pertinencia,
insercao, remocao, uniao, intersecao e diferenca.
Na STL:
- set: arvore vermelho-preto, elementos em ordem, operacoes O(log n);
- unordered_set: tabela hash, sem ordem, operacoes O(1) em media;
- multiset: como set, mas permite repeticoes.
Os algoritmos set_union, set_intersection e set_difference exigem intervalos ordenados.
*/
#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename C>
void mostra(const string &nome, const C &c)
{
  cout << nome << " = { ";
  for (auto x : c) cout << x << " ";
  cout << "}" << endl;
}

int main()
{
  set<int> A = {5, 1, 9, 3, 7, 3};   // o 3 repetido e ignorado; fica em ordem
  set<int> B = {2, 3, 5, 8};
  mostra("A", A); mostra("B", B);

  A.insert(4);
  A.erase(9);
  cout << "7 pertence a A? " << (A.count(7) ? "sim" : "nao") << endl;
  cout << "Menor elemento de A >= 6: " << *A.lower_bound(6) << endl;

  set<int> uniao, inter, dif;
  set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(uniao, uniao.begin()));
  set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(inter, inter.begin()));
  set_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(dif, dif.begin()));
  mostra("A uniao B", uniao); mostra("A inter B", inter); mostra("A - B", dif);
  cout << "B esta contido em A uniao B? " << includes(uniao.begin(), uniao.end(), B.begin(), B.end()) << endl;

  unordered_set<string> visitados = {"home", "login"};
  visitados.insert("perfil");
  cout << "Visitou login? " << (visitados.find("login") != visitados.end() ? "sim" : "nao") << endl;

  multiset<int> notas = {7, 8, 7, 10, 7};
  cout << "Quantas notas 7: " << notas.count(7) << endl;
  return 0;
}
