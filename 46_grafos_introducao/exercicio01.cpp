/*
Exercicio 1. Uma sequencia de inteiros e grafica se existe um grafo simples com esses graus.
Teorema de Havel-Hakimi: ordena em ordem decrescente, tira o primeiro valor d e subtrai 1 dos d seguintes;
a sequencia original e grafica se e somente se a nova for. Para quando tudo zerar (grafica) ou aparecer
valor negativo / faltarem vertices (nao grafica). Construir tambem um grafo com a sequencia, quando existir.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool havelHakimi(vector<int> graus, vector<pair<int, int>> &arestas)
{
  int n = graus.size();
  vector<pair<int, int>> v;   // (grau restante, vertice)
  for (int i = 0; i < n; i++) v.push_back({graus[i], i});
  arestas.clear();
  while (true) {
    sort(v.rbegin(), v.rend());   // decrescente
    if (v[0].first == 0) return true;
    int d = v[0].first;
    if (d > n - 1) return false;  // nao ha vizinhos suficientes
    v[0].first = 0;
    for (int i = 1; i <= d; i++) {
      if (--v[i].first < 0) return false;
      arestas.push_back({v[0].second, v[i].second});   // liga o primeiro aos d seguintes
    }
  }
}

int main()
{
  vector<vector<int>> testes = {{3, 3, 2, 2, 2}, {4, 4, 4, 1, 1}, {3, 3, 3, 3}, {3, 2, 1}, {2, 2, 2, 2, 2, 2}};
  for (auto &t : testes) {
    vector<pair<int, int>> e;
    cout << "{";
    for (size_t i = 0; i < t.size(); i++) cout << (i ? "," : "") << t[i];
    int soma = 0;
    for (int g : t) soma += g;
    cout << "}: ";
    if (soma % 2) { cout << "nao grafica (soma impar)" << endl; continue; }
    if (havelHakimi(t, e)) {
      cout << "grafica, arestas: ";
      for (auto &a : e) cout << a.first << "-" << a.second << " ";
      cout << endl;
    } else cout << "nao grafica" << endl;
  }
  return 0;
}
