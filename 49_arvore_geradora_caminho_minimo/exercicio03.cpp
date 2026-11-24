/*
Exercicio 3. Comparar Kruskal com uma AGM por forca bruta (testar todos os subconjuntos de n - 1 arestas que
formam arvore) em grafos aleatorios pequenos, e contar quantas arvores geradoras cada grafo tem.
Para conferir a contagem, usar o teorema de Cayley no grafo completo: K_n tem n^(n-2) arvores geradoras.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

struct Aresta { int u, v, peso; };

int acha(vector<int> &p, int x) { return p[x] == x ? x : p[x] = acha(p, p[x]); }

int kruskal(int n, vector<Aresta> e)
{
  sort(e.begin(), e.end(), [](const Aresta &a, const Aresta &b) { return a.peso < b.peso; });
  vector<int> p(n);
  for (int i = 0; i < n; i++) p[i] = i;
  int total = 0;
  for (auto &a : e) { int x = acha(p, a.u), y = acha(p, a.v); if (x != y) { p[x] = y; total += a.peso; } }
  return total;
}

// devolve o peso da AGM e conta as arvores geradoras testando todos os subconjuntos de arestas
int forcaBruta(int n, const vector<Aresta> &e, long long &arvores)
{
  int m = e.size(), melhor = INT_MAX;
  arvores = 0;
  for (int mask = 0; mask < (1 << m); mask++) {
    if (__builtin_popcount(mask) != n - 1) continue;   // arvore tem exatamente n - 1 arestas
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i;
    bool ciclo = false;
    int peso = 0;
    for (int i = 0; i < m && !ciclo; i++)
      if (mask >> i & 1) {
        int x = acha(p, e[i].u), y = acha(p, e[i].v);
        if (x == y) ciclo = true; else { p[x] = y; peso += e[i].peso; }
      }
    if (!ciclo) { arvores++; melhor = min(melhor, peso); }   // n - 1 arestas sem ciclo = arvore
  }
  return melhor;
}

int main()
{
  srand(21);
  for (int t = 0; t < 5; t++) {
    int n = 6;
    vector<Aresta> e;
    for (int u = 0; u < n; u++)
      for (int v = u + 1; v < n; v++)
        if (v == u + 1 || rand() % 2) e.push_back({u, v, 1 + rand() % 20});   // caminho 0-1-...-5 garante conexo
    long long arv;
    int fb = forcaBruta(n, e, arv);
    cout << "Grafo " << t + 1 << " (" << e.size() << " arestas): Kruskal = " << kruskal(n, e)
         << ", forca bruta = " << fb << ", arvores geradoras = " << arv << endl;
  }
  vector<Aresta> k5;
  for (int u = 0; u < 5; u++) for (int v = u + 1; v < 5; v++) k5.push_back({u, v, 1});
  long long arv;
  forcaBruta(5, k5, arv);
  cout << "K5: " << arv << " arvores geradoras (Cayley: 5^3 = 125)" << endl;
  return 0;
}
