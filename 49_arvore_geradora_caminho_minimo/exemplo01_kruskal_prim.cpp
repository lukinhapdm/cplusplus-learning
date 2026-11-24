/*
Exemplo 1. Arvore geradora minima (AGM): subgrafo que e arvore, liga todos os vertices de um grafo conexo
ponderado e tem a menor soma de pesos (n - 1 arestas). Dois algoritmos gulosos:
  - Kruskal: ordena as arestas por peso e aceita cada uma que nao forma ciclo (testado com
    union-find: conjuntos disjuntos com uniao por tamanho e compressao de caminho). O(m log m).
  - Prim: cresce uma unica arvore a partir de um vertice; a cada passo adiciona a aresta mais leve
    que sai da arvore (heap minimo). O(m log n).
Ambos se apoiam na propriedade do corte: a aresta mais leve que cruza um corte pertence a alguma AGM.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Aresta { int u, v, peso; };

// union-find
vector<int> pai, tam;
int acha(int x) { return pai[x] == x ? x : pai[x] = acha(pai[x]); }   // compressao de caminho
bool une(int a, int b)
{
  a = acha(a); b = acha(b);
  if (a == b) return false;           // mesmo conjunto: formaria ciclo
  if (tam[a] < tam[b]) swap(a, b);
  pai[b] = a; tam[a] += tam[b];
  return true;
}

void kruskal(int n, vector<Aresta> e)
{
  sort(e.begin(), e.end(), [](const Aresta &a, const Aresta &b) { return a.peso < b.peso; });
  pai.resize(n); tam.assign(n, 1);
  for (int i = 0; i < n; i++) pai[i] = i;
  int total = 0;
  cout << "Kruskal: ";
  for (const Aresta &a : e)
    if (une(a.u, a.v)) { total += a.peso; cout << a.u << "-" << a.v << "(" << a.peso << ") "; }
  cout << "-> peso " << total << endl;
}

void prim(int n, const vector<Aresta> &e)
{
  vector<vector<pair<int, int>>> adj(n);   // (peso, vizinho)
  for (const Aresta &a : e) { adj[a.u].push_back({a.peso, a.v}); adj[a.v].push_back({a.peso, a.u}); }
  vector<bool> naArvore(n, false);
  typedef pair<int, pair<int, int>> Item;  // (peso, (vertice, de onde veio))
  priority_queue<Item, vector<Item>, greater<Item>> heap;
  heap.push({0, {0, -1}});
  int total = 0;
  cout << "Prim:    ";
  while (!heap.empty()) {
    auto [peso, par] = heap.top(); heap.pop();
    int u = par.first;
    if (naArvore[u]) continue;           // entrada velha no heap
    naArvore[u] = true; total += peso;
    if (par.second >= 0) cout << par.second << "-" << u << "(" << peso << ") ";
    for (auto [p, v] : adj[u]) if (!naArvore[v]) heap.push({p, {v, u}});
  }
  cout << "-> peso " << total << endl;
}

int main()
{
  int n = 7;
  vector<Aresta> e = {{0, 1, 7}, {0, 3, 5}, {1, 2, 8}, {1, 3, 9}, {1, 4, 7}, {2, 4, 5},
                      {3, 4, 15}, {3, 5, 6}, {4, 5, 8}, {4, 6, 9}, {5, 6, 11}};
  kruskal(n, e);
  prim(n, e);
  return 0;
}
