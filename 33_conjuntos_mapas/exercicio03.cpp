/*
Exercicio 3. Indice remissivo: para cada palavra, guardar o conjunto (sem repeticao e em ordem) das linhas
em que ela aparece, usando map<string, set<int>>. Depois responder quais linhas contem duas palavras ao mesmo tempo.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
  string linhas[] = {
    "a pilha usa o topo",
    "a fila usa inicio e fim",
    "o heap e uma arvore guardada em vetor",
    "a pilha e a fila podem usar vetor",
    "a arvore de busca usa ponteiros"
  };
  map<string, set<int>> indice;
  for (int i = 0; i < 5; i++) {
    stringstream ss(linhas[i]);
    string p;
    while (ss >> p) if (p.size() > 2) indice[p].insert(i + 1);   // ignora palavras curtas
  }

  for (const auto &e : indice) {
    cout << e.first << ": ";
    for (int l : e.second) cout << l << " ";
    cout << endl;
  }

  const set<int> &a = indice["vetor"], &b = indice["pilha"];
  set<int> ambas;
  set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(ambas, ambas.begin()));
  cout << "\nLinhas com 'vetor' e 'pilha': ";
  for (int l : ambas) cout << l << " ";
  cout << endl;
  return 0;
}
