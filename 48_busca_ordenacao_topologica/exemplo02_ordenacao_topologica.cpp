/*
Exemplo 2. Ordenacao topologica de um digrafo aciclico (DAG): ordem linear dos vertices em que todo arco
u -> v tem u antes de v (ex.: tarefas com dependencias). So existe se o grafo nao tiver ciclo.
  - Kahn: repete "tira um vertice com grau de entrada 0 e diminui o grau de entrada dos vizinhos".
    Se sobrarem vertices, ha ciclo.
  - Por DFS: a ordem decrescente de termino (f[u]) e uma ordenacao topologica.
Ambos O(n + m).
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

vector<string> nome = {"cueca", "calca", "cinto", "camisa", "gravata", "paleto", "meias", "sapatos", "relogio"};

vector<int> kahn(const vector<vector<int>> &adj)
{
  int n = adj.size();
  vector<int> entrada(n, 0), ordem;
  for (int u = 0; u < n; u++) for (int v : adj[u]) entrada[v]++;
  queue<int> livres;
  for (int u = 0; u < n; u++) if (entrada[u] == 0) livres.push(u);
  while (!livres.empty()) {
    int u = livres.front(); livres.pop();
    ordem.push_back(u);
    for (int v : adj[u]) if (--entrada[v] == 0) livres.push(v);   // dependencias satisfeitas
  }
  return ordem;   // se ordem.size() < n, ha ciclo
}

void dfs(const vector<vector<int>> &adj, int u, vector<bool> &vis, vector<int> &pilha)
{
  vis[u] = true;
  for (int v : adj[u]) if (!vis[v]) dfs(adj, v, vis, pilha);
  pilha.push_back(u);   // termina depois de todos os seus sucessores
}

int main()
{
  // vestir-se: cada arco u -> v diz que u vem antes de v
  vector<vector<int>> adj(9);
  int arcos[][2] = {{0, 1}, {0, 7}, {1, 2}, {1, 7}, {3, 2}, {3, 4}, {2, 5}, {4, 5}, {6, 7}};
  for (auto &a : arcos) adj[a[0]].push_back(a[1]);

  cout << "Kahn: ";
  for (int u : kahn(adj)) cout << nome[u] << " ";
  cout << endl;

  vector<bool> vis(9, false);
  vector<int> pilha;
  for (int u = 0; u < 9; u++) if (!vis[u]) dfs(adj, u, vis, pilha);
  reverse(pilha.begin(), pilha.end());
  cout << "DFS:  ";
  for (int u : pilha) cout << nome[u] << " ";
  cout << endl;

  adj[5].push_back(1);   // paleto antes da calca: cria ciclo calca -> cinto -> paleto -> calca
  vector<int> o = kahn(adj);
  cout << "Com o arco paleto -> calca: " << o.size() << " de 9 vertices ordenados -> "
       << (o.size() < 9 ? "ha ciclo" : "sem ciclo") << endl;
  return 0;
}
