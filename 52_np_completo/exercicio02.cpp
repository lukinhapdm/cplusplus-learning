/*
Exercicio 2. Caixeiro viajante (TSP, NP-dificil) com tres abordagens:
  (a) forca bruta: (n-1)! ciclos;
  (b) programacao dinamica de Held-Karp: D[S][v] = menor caminho que sai de 0, visita exatamente o conjunto S
      e termina em v. O(n^2 2^n): ainda exponencial, mas muito melhor que (n-1)!;
  (c) heuristica do vizinho mais proximo: O(n^2), rapida mas sem garantia de otimo.
Para problemas NP-dificeis na pratica: algoritmos exatos exponenciais melhores, heuristicas ou aproximacoes.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
using namespace std;

int n;
vector<vector<int>> d;

int forcaBruta()
{
  vector<int> p(n);
  for (int i = 0; i < n; i++) p[i] = i;
  int melhor = INT_MAX;
  do {
    int c = 0;
    for (int i = 0; i < n; i++) c += d[p[i]][p[(i + 1) % n]];
    melhor = min(melhor, c);
  } while (next_permutation(p.begin() + 1, p.end()));
  return melhor;
}

int heldKarp()
{
  const int INF = INT_MAX / 2;
  vector<vector<int>> D(1 << n, vector<int>(n, INF));
  D[1][0] = 0;   // conjunto {0}, parado em 0
  for (int S = 1; S < (1 << n); S++) {
    if (!(S & 1)) continue;   // todo caminho comeca em 0
    for (int v = 0; v < n; v++) {
      if (!(S >> v & 1) || D[S][v] >= INF) continue;
      for (int w = 0; w < n; w++)
        if (!(S >> w & 1)) D[S | 1 << w][w] = min(D[S | 1 << w][w], D[S][v] + d[v][w]);   // estende ate w
    }
  }
  int melhor = INF;
  for (int v = 1; v < n; v++) melhor = min(melhor, D[(1 << n) - 1][v] + d[v][0]);   // volta para 0
  return melhor;
}

int vizinhoMaisProximo()
{
  vector<bool> vis(n, false);
  int u = 0, total = 0;
  vis[0] = true;
  for (int passo = 1; passo < n; passo++) {
    int prox = -1;
    for (int v = 0; v < n; v++) if (!vis[v] && (prox < 0 || d[u][v] < d[u][prox])) prox = v;
    total += d[u][prox]; vis[prox] = true; u = prox;
  }
  return total + d[u][0];
}

int main()
{
  srand(8);
  for (n = 6; n <= 10; n += 2) {
    vector<pair<int, int>> pts(n);
    for (auto &p : pts) p = {rand() % 100, rand() % 100};
    d.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) d[i][j] = (int)round(hypot(pts[i].first - pts[j].first, pts[i].second - pts[j].second));
    cout << "n = " << n << ": forca bruta = " << forcaBruta() << ", Held-Karp = " << heldKarp()
         << ", vizinho mais proximo = " << vizinhoMaisProximo() << endl;
  }
  n = 16;   // forca bruta ja seria inviavel (15! = 1.3 trilhao de ciclos)
  vector<pair<int, int>> pts(n);
  for (auto &p : pts) p = {rand() % 100, rand() % 100};
  d.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) d[i][j] = (int)round(hypot(pts[i].first - pts[j].first, pts[i].second - pts[j].second));
  cout << "n = 16: Held-Karp = " << heldKarp() << ", vizinho mais proximo = " << vizinhoMaisProximo() << endl;
  return 0;
}
