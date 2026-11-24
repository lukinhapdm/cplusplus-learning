/*
Exemplo 1. Conjunto independente: vertices dois a dois NAO adjacentes. Clique: vertices dois a dois adjacentes.
alfa(G) = tamanho do maior conjunto independente; omega(G) = tamanho da maior clique.
Relacao: S e independente em G se e somente se S e clique no complemento de G, logo alfa(G) = omega(G').
Tambem: S e independente se e somente se V - S e cobertura de vertices (toda aresta tem ponta em V - S).
Encontrar alfa ou omega e NP-dificil; aqui usamos forca bruta sobre os 2^n subconjuntos (n pequeno),
com cada subconjunto representado por uma mascara de bits e a vizinhanca de u por adj[u] (tambem bits).
*/
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<unsigned> adj;   // bit v de adj[u] ligado se u-v e aresta

bool independente(unsigned S)
{
  for (int u = 0; u < n; u++) if ((S >> u & 1) && (adj[u] & S)) return false;   // u tem vizinho dentro de S
  return true;
}

bool clique(unsigned S)
{
  for (int u = 0; u < n; u++)
    if (S >> u & 1) if (((adj[u] | (1u << u)) & S) != S) return false;   // algum vertice de S nao e vizinho de u
  return true;
}

void mostra(unsigned S) { cout << "{"; for (int u = 0; u < n; u++) if (S >> u & 1) cout << " " << u; cout << " }"; }

int main()
{
  n = 8;
  adj.assign(n, 0);
  int e[][2] = {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {5, 6}, {5, 7}, {6, 7}, {1, 4}, {2, 4}};
  for (auto &a : e) { adj[a[0]] |= 1u << a[1]; adj[a[1]] |= 1u << a[0]; }

  unsigned melhorI = 0, melhorC = 0;
  for (unsigned S = 0; S < (1u << n); S++) {
    int tam = __builtin_popcount(S);
    if (tam > __builtin_popcount(melhorI) && independente(S)) melhorI = S;
    if (tam > __builtin_popcount(melhorC) && clique(S)) melhorC = S;
  }
  cout << "Maior conjunto independente: "; mostra(melhorI); cout << " alfa = " << __builtin_popcount(melhorI) << endl;
  cout << "Cobertura de vertices minima (complemento): "; mostra(~melhorI & ((1u << n) - 1)); cout << endl;
  cout << "Maior clique: "; mostra(melhorC); cout << " omega = " << __builtin_popcount(melhorC) << endl;

  // no complemento, as cliques viram conjuntos independentes
  vector<unsigned> original = adj;
  for (int u = 0; u < n; u++) adj[u] = ~original[u] & ((1u << n) - 1) & ~(1u << u);
  cout << "No complemento, a clique "; mostra(melhorC);
  cout << (independente(melhorC) ? " e" : " nao e") << " conjunto independente" << endl;
  return 0;
}
