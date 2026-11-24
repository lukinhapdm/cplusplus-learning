/*
Exemplo 2. Conectividade: um grafo e conexo se existe caminho entre todo par de vertices; senao ele se
divide em componentes conexas (encontradas com uma busca a partir de cada vertice ainda nao visitado).
Pontos fracos da conectividade:
  - ponte: aresta cuja remocao aumenta o numero de componentes;
  - articulacao (vertice de corte): vertice cuja remocao aumenta o numero de componentes.
Algoritmo de Tarjan (uma busca em profundidade, O(n + m)): desc[u] = ordem de descoberta e
low[u] = menor desc alcancavel a partir da subarvore de u usando no maximo uma aresta de retorno.
  - aresta u-v (v filho) e ponte se low[v] > desc[u];
  - u (nao raiz) e articulacao se tem filho v com low[v] >= desc[u]; a raiz e se tiver 2 ou mais filhos.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, tempo;
vector<vector<int>> adj;
vector<int> desc_, low, comp;
vector<bool> articulacao;
vector<pair<int, int>> pontes;

void dfs(int u, int pai)
{
  desc_[u] = low[u] = ++tempo;
  int filhos = 0;
  for (int v : adj[u]) {
    if (v == pai) continue;
    if (desc_[v]) low[u] = min(low[u], desc_[v]);   // aresta de retorno
    else {
      filhos++;
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > desc_[u]) pontes.push_back({u, v});
      if (pai != -1 && low[v] >= desc_[u]) articulacao[u] = true;
    }
  }
  if (pai == -1 && filhos > 1) articulacao[u] = true;
}

void marcaComponente(int u, int c)
{
  comp[u] = c;
  for (int v : adj[u]) if (comp[v] < 0) marcaComponente(v, c);
}

int main()
{
  n = 10;
  adj.assign(n, {});
  int e[][2] = {{0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 5}, {5, 3}, {5, 6}, {7, 8}};   // 9 isolado
  for (auto &x : e) { adj[x[0]].push_back(x[1]); adj[x[1]].push_back(x[0]); }

  comp.assign(n, -1);
  int c = 0;
  for (int u = 0; u < n; u++) if (comp[u] < 0) marcaComponente(u, c++);
  cout << c << " componentes conexas:" << endl;
  for (int k = 0; k < c; k++) {
    cout << "  {";
    for (int u = 0; u < n; u++) if (comp[u] == k) cout << " " << u;
    cout << " }" << endl;
  }

  desc_.assign(n, 0); low.assign(n, 0); articulacao.assign(n, false); tempo = 0;
  for (int u = 0; u < n; u++) if (!desc_[u]) dfs(u, -1);
  cout << "Pontes: ";
  for (auto &p : pontes) cout << p.first << "-" << p.second << " ";
  cout << "\nArticulacoes: ";
  for (int u = 0; u < n; u++) if (articulacao[u]) cout << u << " ";
  cout << endl;
  return 0;
}
