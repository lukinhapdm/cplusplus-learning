/*
Exercicio 3. Detectar e MOSTRAR um ciclo em um digrafo usando DFS com tres cores:
branco (nao visitado), cinza (na pilha de recursao) e preto (terminado). Um arco para um vertice cinza
fecha um ciclo; o ciclo e recuperado seguindo os pais a partir do vertice atual.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum Cor { BRANCO, CINZA, PRETO };
vector<vector<int>> adj;
vector<Cor> cor;
vector<int> pai, ciclo;

bool dfs(int u)
{
  cor[u] = CINZA;
  for (int v : adj[u]) {
    if (cor[v] == CINZA) {   // arco de retorno: ciclo v -> ... -> u -> v
      for (int x = u; x != v; x = pai[x]) ciclo.push_back(x);
      ciclo.push_back(v);
      reverse(ciclo.begin(), ciclo.end());
      return true;
    }
    if (cor[v] == BRANCO) { pai[v] = u; if (dfs(v)) return true; }
  }
  cor[u] = PRETO;
  return false;
}

void testa(int n, const vector<pair<int, int>> &arcos)
{
  adj.assign(n, {}); cor.assign(n, BRANCO); pai.assign(n, -1); ciclo.clear();
  for (auto &a : arcos) adj[a.first].push_back(a.second);
  bool achou = false;
  for (int u = 0; u < n && !achou; u++) if (cor[u] == BRANCO) achou = dfs(u);
  if (!achou) { cout << "Aciclico (DAG)" << endl; return; }
  cout << "Ciclo: ";
  for (int x : ciclo) cout << x << " -> ";
  cout << ciclo[0] << endl;
}

int main()
{
  testa(6, {{0, 1}, {1, 2}, {2, 3}, {0, 3}, {3, 4}, {4, 5}});
  testa(6, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}, {4, 5}});
  testa(4, {{0, 1}, {0, 2}, {1, 3}, {2, 3}});   // losango: dois caminhos, mas sem ciclo
  return 0;
}
