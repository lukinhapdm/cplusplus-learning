/*
Exemplo 1. Busca em grafos, ambas O(n + m) com lista de adjacencia.
Busca em largura (BFS): usa fila; visita os vertices em camadas de distancia crescente a partir da origem.
  Da a menor distancia em numero de arestas e uma arvore de caminhos minimos (vetor de pais).
Busca em profundidade (DFS): usa recursao (pilha); vai o mais fundo possivel antes de voltar.
  Registra tempo de descoberta d[u] e de termino f[u]. Num digrafo as arestas u -> v se classificam em:
  - arvore: v descoberto agora por u;          - retorno: v ainda aberto (ancestral) -> indica ciclo;
  - avanco: v descendente ja terminado;       - cruzamento: v em outro ramo, ja terminado.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(const vector<vector<int>> &adj, int s)
{
  int n = adj.size();
  vector<int> dist(n, -1), pai(n, -1);
  queue<int> f;
  dist[s] = 0; f.push(s);
  while (!f.empty()) {
    int u = f.front(); f.pop();
    for (int v : adj[u])
      if (dist[v] == -1) { dist[v] = dist[u] + 1; pai[v] = u; f.push(v); }
  }
  cout << "BFS a partir de " << s << ":" << endl;
  for (int u = 0; u < n; u++) {
    cout << "  " << u << ": distancia " << dist[u] << ", caminho ";
    vector<int> c;
    for (int x = u; x != -1; x = pai[x]) c.push_back(x);
    for (int i = c.size() - 1; i >= 0; i--) cout << c[i] << (i ? "-" : "");
    cout << endl;
  }
}

vector<int> d, f, estado;   // estado: 0 = nao visitado, 1 = aberto, 2 = terminado
int tempo;

void dfs(const vector<vector<int>> &adj, int u)
{
  d[u] = ++tempo; estado[u] = 1;
  for (int v : adj[u]) {
    if (estado[v] == 0) { cout << "  " << u << "->" << v << " arvore" << endl; dfs(adj, v); }
    else if (estado[v] == 1) cout << "  " << u << "->" << v << " retorno" << endl;
    else if (d[u] < d[v]) cout << "  " << u << "->" << v << " avanco" << endl;
    else cout << "  " << u << "->" << v << " cruzamento" << endl;
  }
  f[u] = ++tempo; estado[u] = 2;
}

int main()
{
  vector<vector<int>> g = {{1, 2}, {0, 3, 4}, {0, 4}, {1, 5}, {1, 2, 5}, {3, 4}};   // nao direcionado
  bfs(g, 0);

  vector<vector<int>> dg = {{1, 2, 3}, {3}, {1, 3}, {0}, {3, 5}, {}};                  // digrafo
  int n = dg.size();
  d.assign(n, 0); f.assign(n, 0); estado.assign(n, 0); tempo = 0;
  cout << "DFS no digrafo (classificacao dos arcos):" << endl;
  for (int u = 0; u < n; u++) if (!estado[u]) dfs(dg, u);
  for (int u = 0; u < n; u++) cout << "  " << u << ": d = " << d[u] << ", f = " << f[u] << endl;
  return 0;
}
