/*
Exercicio 1. Bellman-Ford: caminhos mais curtos de origem unica aceitando pesos NEGATIVOS.
Relaxa todos os arcos n - 1 vezes (um caminho minimo tem no maximo n - 1 arcos). Se na n-esima rodada
ainda for possivel melhorar alguma distancia, existe ciclo de peso negativo alcancavel (nao ha minimo).
Custo O(nm). Mostrar tambem que Dijkstra erra no mesmo grafo com arco negativo.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Arco { int u, v, w; };
const long long INF = LLONG_MAX / 4;

bool bellmanFord(int n, const vector<Arco> &a, int s, vector<long long> &dist)
{
  dist.assign(n, INF);
  dist[s] = 0;
  for (int rodada = 1; rodada < n; rodada++) {
    bool mudou = false;
    for (const Arco &x : a)
      if (dist[x.u] < INF && dist[x.u] + x.w < dist[x.v]) { dist[x.v] = dist[x.u] + x.w; mudou = true; }
    if (!mudou) break;   // estabilizou antes
  }
  for (const Arco &x : a)
    if (dist[x.u] < INF && dist[x.u] + x.w < dist[x.v]) return false;   // ainda melhora: ciclo negativo
  return true;
}

vector<long long> dijkstra(int n, const vector<Arco> &a, int s)
{
  vector<vector<pair<int, int>>> adj(n);
  for (const Arco &x : a) adj[x.u].push_back({x.v, x.w});
  vector<long long> dist(n, INF);
  vector<bool> fixado(n, false);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> h;
  dist[s] = 0; h.push({0, s});
  while (!h.empty()) {
    int u = h.top().second; h.pop();
    if (fixado[u]) continue;
    fixado[u] = true;
    for (auto [v, w] : adj[u])
      if (!fixado[v] && dist[u] + w < dist[v]) { dist[v] = dist[u] + w; h.push({dist[v], v}); }
  }
  return dist;
}

int main()
{
  int n = 4;
  vector<Arco> a = {{0, 1, 1}, {0, 2, 4}, {2, 1, -5}, {1, 3, 2}};
  vector<long long> d;
  bellmanFord(n, a, 0, d);
  vector<long long> dj = dijkstra(n, a, 0);
  cout << "vertice  Bellman-Ford  Dijkstra" << endl;
  for (int v = 0; v < n; v++) cout << "   " << v << "          " << d[v] << "          " << dj[v] << endl;
  cout << "(Dijkstra fixou o vertice 1 com 1 antes de descobrir o caminho 0->2->1 de custo -1)" << endl;

  a.push_back({1, 2, 3});   // ciclo 2 -> 1 -> 2 com peso -5 + 3 = -2
  cout << "Com o arco 1->2 (peso 3): " << (bellmanFord(n, a, 0, d) ? "sem" : "ha") << " ciclo negativo" << endl;
  return 0;
}
