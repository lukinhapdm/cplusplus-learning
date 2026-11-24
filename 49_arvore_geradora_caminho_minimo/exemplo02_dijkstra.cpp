/*
Exemplo 2. Caminho mais curto de origem unica com pesos NAO negativos: algoritmo de Dijkstra.
Mantem dist[v] = melhor distancia conhecida. A cada passo fixa o vertice nao fixado de menor dist
(heap minimo) e "relaxa" seus arcos: se dist[u] + w(u,v) < dist[v], atualiza dist[v] e pai[v] = u.
Guloso correto porque, sem pesos negativos, o menor dist ainda aberto nao pode melhorar depois.
Custo O((n + m) log n). Com peso negativo pode errar (ver Bellman-Ford nos exercicios).
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
using namespace std;

int main()
{
  vector<string> nome = {"Casa", "Padaria", "Escola", "Mercado", "Parque", "Trabalho"};
  int n = nome.size();
  vector<vector<pair<int, int>>> adj(n);   // (vizinho, minutos)
  auto via = [&](int u, int v, int w) { adj[u].push_back({v, w}); adj[v].push_back({u, w}); };
  via(0, 1, 4); via(0, 2, 2); via(1, 2, 1); via(1, 3, 5); via(2, 3, 8); via(2, 4, 10);
  via(3, 4, 2); via(3, 5, 6); via(4, 5, 3);

  vector<int> dist(n, INT_MAX), pai(n, -1);
  vector<bool> fixado(n, false);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;   // (dist, vertice)
  dist[0] = 0; heap.push({0, 0});
  while (!heap.empty()) {
    int u = heap.top().second; heap.pop();
    if (fixado[u]) continue;
    fixado[u] = true;
    for (auto [v, w] : adj[u])
      if (dist[u] + w < dist[v]) {   // relaxamento
        dist[v] = dist[u] + w; pai[v] = u;
        heap.push({dist[v], v});
      }
  }
  for (int v = 1; v < n; v++) {
    vector<int> c;
    for (int x = v; x != -1; x = pai[x]) c.push_back(x);
    cout << nome[v] << ": " << dist[v] << " min (";
    for (int i = c.size() - 1; i >= 0; i--) cout << nome[c[i]] << (i ? " -> " : ")");
    cout << endl;
  }
  return 0;
}
