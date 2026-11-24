/*
Exemplo 2. Reducao polinomial A <=p B: transforma, em tempo polinomial, qualquer instancia de A numa instancia
de B com a MESMA resposta. Assim, um algoritmo para B resolve A ("B e pelo menos tao dificil quanto A").
Para provar que B e NP-completo: mostrar que B esta em NP e reduzir a B um problema ja sabido NP-completo.
Reducoes simples entre tres problemas NP-completos em um grafo G com n vertices:
  - CONJUNTO INDEPENDENTE (G, k)  <=>  CLIQUE (complemento de G, k)
  - CONJUNTO INDEPENDENTE (G, k)  <=>  COBERTURA DE VERTICES (G, n - k)
O programa resolve so CLIQUE (forca bruta) e responde os outros dois pelas reducoes, conferindo com
resolucoes diretas.
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef vector<vector<bool>> Grafo;

bool temClique(const Grafo &g, int k)   // o "algoritmo de B"
{
  int n = g.size();
  for (int S = 0; S < (1 << n); S++) {
    if (__builtin_popcount(S) != k) continue;
    bool ok = true;
    for (int u = 0; u < n && ok; u++)
      for (int v = u + 1; v < n && ok; v++) if ((S >> u & 1) && (S >> v & 1) && !g[u][v]) ok = false;
    if (ok) return true;
  }
  return false;
}

Grafo complemento(const Grafo &g)   // a transformacao: O(n^2)
{
  int n = g.size();
  Grafo c(n, vector<bool>(n, false));
  for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) if (u != v) c[u][v] = !g[u][v];
  return c;
}

bool independentePorReducao(const Grafo &g, int k) { return temClique(complemento(g), k); }
bool coberturaPorReducao(const Grafo &g, int c) { return independentePorReducao(g, g.size() - c); }

// resolucoes diretas, so para conferir
bool independenteDireto(const Grafo &g, int k)
{
  int n = g.size();
  for (int S = 0; S < (1 << n); S++) {
    if (__builtin_popcount(S) != k) continue;
    bool ok = true;
    for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) if ((S >> u & 1) && (S >> v & 1) && g[u][v]) ok = false;
    if (ok) return true;
  }
  return false;
}

bool coberturaDireta(const Grafo &g, int c)
{
  int n = g.size();
  for (int S = 0; S < (1 << n); S++) {
    if (__builtin_popcount(S) != c) continue;
    bool ok = true;
    for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) if (g[u][v] && !(S >> u & 1) && !(S >> v & 1)) ok = false;
    if (ok) return true;
  }
  return false;
}

int main()
{
  srand(2);
  int n = 9, erros = 0;
  for (int t = 0; t < 20; t++) {
    Grafo g(n, vector<bool>(n, false));
    for (int u = 0; u < n; u++) for (int v = u + 1; v < n; v++) if (rand() % 3 == 0) g[u][v] = g[v][u] = true;
    for (int k = 0; k <= n; k++) {
      if (independentePorReducao(g, k) != independenteDireto(g, k)) erros++;
      if (coberturaPorReducao(g, k) != coberturaDireta(g, k)) erros++;
    }
    if (t == 0) {
      int alfa = 0;
      while (alfa < n && independentePorReducao(g, alfa + 1)) alfa++;
      cout << "Grafo 1: maior independente = " << alfa << " (via CLIQUE no complemento), menor cobertura = " << n - alfa << endl;
    }
  }
  cout << "20 grafos x 10 valores de k: " << erros << " respostas diferentes entre reducao e resolucao direta" << endl;
  return 0;
}
