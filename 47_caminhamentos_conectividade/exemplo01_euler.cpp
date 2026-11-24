/*
Exemplo 1. Caminhamentos: passeio (pode repetir tudo), trilha (nao repete aresta), caminho (nao repete
vertice), circuito/ciclo (fechados). Problema das pontes de Konigsberg -> grafos eulerianos:
  - circuito euleriano (passa por TODAS as arestas uma vez e volta ao inicio) existe se e somente se o grafo
    e conexo (desconsiderando vertices isolados) e todos os vertices tem grau par;
  - trilha euleriana aberta existe se exatamente 2 vertices tem grau impar (ela comeca em um e termina no outro).
Algoritmo de Hierholzer, O(m): anda por arestas ainda nao usadas ate travar; ao travar, o vertice entra
no circuito final e a busca continua a partir do anterior que ainda tem arestas livres (pilha).
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct Grafo {
  int n;
  vector<vector<pair<int, int>>> adj;   // (vizinho, id da aresta)
  int m = 0;
  Grafo(int n) : n(n), adj(n) {}
  void aresta(int u, int v) { adj[u].push_back({v, m}); adj[v].push_back({u, m}); m++; }
};

bool conexo(const Grafo &g)   // considera so vertices com arestas
{
  vector<bool> vis(g.n, false);
  int inicio = -1;
  for (int u = 0; u < g.n; u++) if (!g.adj[u].empty()) { inicio = u; break; }
  if (inicio < 0) return true;
  stack<int> p; p.push(inicio); vis[inicio] = true;
  while (!p.empty()) {
    int u = p.top(); p.pop();
    for (auto &e : g.adj[u]) if (!vis[e.first]) { vis[e.first] = true; p.push(e.first); }
  }
  for (int u = 0; u < g.n; u++) if (!g.adj[u].empty() && !vis[u]) return false;
  return true;
}

void euler(const Grafo &g, const char *nome)
{
  vector<int> impares;
  for (int u = 0; u < g.n; u++) if (g.adj[u].size() % 2) impares.push_back(u);
  cout << nome << ": ";
  if (!conexo(g) || (impares.size() != 0 && impares.size() != 2)) {
    cout << "nao euleriano (" << impares.size() << " vertices de grau impar)" << endl;
    return;
  }
  int inicio = impares.empty() ? 0 : impares[0];
  while (g.adj[inicio].empty()) inicio++;
  vector<bool> usada(g.m, false);
  vector<size_t> prox(g.n, 0);   // proxima aresta a examinar de cada vertice
  vector<int> circuito;
  stack<int> p;
  p.push(inicio);
  while (!p.empty()) {
    int u = p.top();
    while (prox[u] < g.adj[u].size() && usada[g.adj[u][prox[u]].second]) prox[u]++;
    if (prox[u] == g.adj[u].size()) { circuito.push_back(u); p.pop(); }   // travou: entra no resultado
    else {
      auto e = g.adj[u][prox[u]];
      usada[e.second] = true;
      p.push(e.first);
    }
  }
  reverse(circuito.begin(), circuito.end());
  cout << (impares.empty() ? "circuito euleriano: " : "trilha euleriana: ");
  for (size_t i = 0; i < circuito.size(); i++) cout << (i ? "-" : "") << circuito[i];
  cout << endl;
}

int main()
{
  Grafo k(4);   // Konigsberg (multigrafo): 0 = ilha, 1 e 2 = margens, 3 = outra ilha
  k.aresta(0, 1); k.aresta(0, 1); k.aresta(0, 2); k.aresta(0, 2); k.aresta(0, 3); k.aresta(1, 3); k.aresta(2, 3);
  euler(k, "Konigsberg");

  Grafo casa(5);   // "casinha" desenhada sem tirar o lapis
  int e[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}, {1, 3}, {2, 4}, {3, 4}};
  for (auto &x : e) casa.aresta(x[0], x[1]);
  euler(casa, "Casinha");

  Grafo c(5);   // dois triangulos ligados por um vertice: todos os graus pares
  int f[][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 2}};
  for (auto &x : f) c.aresta(x[0], x[1]);
  euler(c, "Gravata");
  return 0;
}
