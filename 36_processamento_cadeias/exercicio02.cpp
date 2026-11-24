/*
Exercicio 2. Arquivo invertido para uma colecao de documentos: a lista de ocorrencias guarda o numero dos
documentos (ordenados, sem repeticao) em que cada palavra aparece. Implementar consultas booleanas:
  - "a E b": intersecao das listas;   - "a OU b": uniao;   - "a E NAO b": diferenca.
As listas ordenadas permitem fazer cada operacao com uma intercalacao em tempo linear.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

map<string, vector<int>> indice;

void indexa(int doc, const string &texto)
{
  stringstream ss(texto);
  string p;
  while (ss >> p) {
    vector<int> &lista = indice[p];
    if (lista.empty() || lista.back() != doc) lista.push_back(doc);   // documentos chegam em ordem
  }
}

vector<int> lista(const string &p) { auto it = indice.find(p); return it == indice.end() ? vector<int>() : it->second; }

vector<int> E(const vector<int> &a, const vector<int> &b)
{
  vector<int> r;
  size_t i = 0, j = 0;
  while (i < a.size() && j < b.size()) {
    if (a[i] == b[j]) { r.push_back(a[i]); i++; j++; }
    else if (a[i] < b[j]) i++;
    else j++;
  }
  return r;
}

vector<int> OU(const vector<int> &a, const vector<int> &b)
{
  vector<int> r;
  size_t i = 0, j = 0;
  while (i < a.size() || j < b.size()) {
    if (j == b.size() || (i < a.size() && a[i] < b[j])) r.push_back(a[i++]);
    else if (i == a.size() || b[j] < a[i]) r.push_back(b[j++]);
    else { r.push_back(a[i]); i++; j++; }
  }
  return r;
}

vector<int> ENAO(const vector<int> &a, const vector<int> &b)
{
  vector<int> r;
  size_t j = 0;
  for (int x : a) {
    while (j < b.size() && b[j] < x) j++;
    if (j == b.size() || b[j] != x) r.push_back(x);
  }
  return r;
}

void mostra(const string &consulta, const vector<int> &r)
{
  cout << consulta << ": ";
  for (int d : r) cout << "doc" << d << " ";
  if (r.empty()) cout << "(nenhum)";
  cout << endl;
}

int main()
{
  indexa(1, "arvore b para memoria secundaria");
  indexa(2, "arvore avl e arvore vermelho preto");
  indexa(3, "hash com memoria secundaria");
  indexa(4, "arvore patricia e trie");
  indexa(5, "pesquisa binaria em memoria principal");

  mostra("arvore E memoria", E(lista("arvore"), lista("memoria")));
  mostra("arvore OU hash", OU(lista("arvore"), lista("hash")));
  mostra("memoria E NAO arvore", ENAO(lista("memoria"), lista("arvore")));
  mostra("(arvore OU hash) E secundaria", E(OU(lista("arvore"), lista("hash")), lista("secundaria")));
  return 0;
}
