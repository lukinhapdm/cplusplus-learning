/*
Exemplo 2. Coloracao de vertices: atribuir cores de modo que vertices adjacentes tenham cores diferentes.
Numero cromatico chi(G) = menor numero de cores possivel (decidir se chi(G) <= k e NP-completo para k >= 3).
Limites: omega(G) <= chi(G) <= grau maximo + 1.
  - Guloso: percorre os vertices numa ordem e da a cada um a menor cor nao usada pelos vizinhos.
    Rapido, usa no maximo grau maximo + 1 cores, mas o resultado depende da ordem.
  - Welsh-Powell: guloso na ordem de grau decrescente (costuma usar menos cores).
  - Exato: backtracking testando k = 1, 2, 3... ate conseguir colorir.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;

int gulosa(const vector<int> &ordem, vector<int> &cor)
{
  int n = adj.size(), maior = 0;
  cor.assign(n, -1);
  for (int u : ordem) {
    vector<bool> usada(n + 1, false);
    for (int v : adj[u]) if (cor[v] >= 0) usada[cor[v]] = true;
    int c = 0;
    while (usada[c]) c++;   // menor cor livre
    cor[u] = c;
    maior = max(maior, c + 1);
  }
  return maior;
}

bool colore(int u, int k, vector<int> &cor)
{
  if (u == (int)adj.size()) return true;
  for (int c = 0; c < k; c++) {
    bool ok = true;
    for (int v : adj[u]) if (cor[v] == c) ok = false;
    if (!ok) continue;
    cor[u] = c;
    if (colore(u + 1, k, cor)) return true;
    cor[u] = -1;
  }
  return false;
}

void mostra(const char *nome, int k, const vector<int> &cor)
{
  cout << nome << ": " << k << " cores -> ";
  for (size_t u = 0; u < cor.size(); u++) cout << u << ":" << cor[u] << " ";
  cout << endl;
}

int main()
{
  // grafo "coroa" de 8 vertices: bipartido (2 cores), mas a ordem 0,1,2,... engana o guloso
  int n = 8;
  adj.assign(n, {});
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (i != j) { adj[2 * i].push_back(2 * j + 1); adj[2 * j + 1].push_back(2 * i); }   // a_i ~ b_j, i != j

  vector<int> cor, ordem(n);
  for (int i = 0; i < n; i++) ordem[i] = i;
  mostra("Guloso na ordem 0..7  ", gulosa(ordem, cor), cor);

  sort(ordem.begin(), ordem.end(), [](int a, int b) { return adj[a].size() > adj[b].size(); });
  mostra("Welsh-Powell          ", gulosa(ordem, cor), cor);   // todos tem grau 3: ordenar por grau nao ajuda

  ordem = {0, 2, 4, 6, 1, 3, 5, 7};   // primeiro um lado da biparticao, depois o outro
  mostra("Guloso 0,2,4,6,1,3,5,7", gulosa(ordem, cor), cor);

  for (int k = 1; k <= n; k++) {
    cor.assign(n, -1);
    if (colore(0, k, cor)) { mostra("Exato (backtracking)  ", k, cor); break; }
  }
  return 0;
}
