/*
Exercicio 3. Em digrafos, componente fortemente conexa (CFC) e um conjunto maximo de vertices em que todo
par u, v tem caminho u -> v E v -> u. Algoritmo de Kosaraju, O(n + m):
  1) DFS no grafo, empilhando cada vertice quando ele termina;
  2) DFS no grafo transposto (arcos invertidos), na ordem de desempilhamento: cada arvore e uma CFC.
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n;
vector<vector<int>> adj, transp;
vector<bool> vis;
stack<int> ordem;

void dfs1(int u)
{
  vis[u] = true;
  for (int v : adj[u]) if (!vis[v]) dfs1(v);
  ordem.push(u);   // terminou
}

void dfs2(int u, int c, vector<int> &comp)
{
  comp[u] = c;
  for (int v : transp[u]) if (comp[v] < 0) dfs2(v, c, comp);
}

int main()
{
  n = 8;
  adj.assign(n, {}); transp.assign(n, {});
  int arcos[][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 5}, {5, 3}, {6, 5}, {6, 7}, {7, 6}};
  for (auto &a : arcos) { adj[a[0]].push_back(a[1]); transp[a[1]].push_back(a[0]); }

  vis.assign(n, false);
  for (int u = 0; u < n; u++) if (!vis[u]) dfs1(u);

  vector<int> comp(n, -1);
  int c = 0;
  while (!ordem.empty()) {
    int u = ordem.top(); ordem.pop();
    if (comp[u] < 0) dfs2(u, c++, comp);
  }
  cout << c << " componentes fortemente conexas:" << endl;
  for (int k = 0; k < c; k++) {
    cout << "  {";
    for (int u = 0; u < n; u++) if (comp[u] == k) cout << " " << u;
    cout << " }" << endl;
  }
  return 0;
}
