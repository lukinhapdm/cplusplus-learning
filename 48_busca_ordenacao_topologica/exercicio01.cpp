/*
Exercicio 1. Menor caminho num labirinto: cada casa livre ('.') e um vertice ligado as casas livres vizinhas
(cima, baixo, esquerda, direita). Usar BFS a partir de S para achar a menor quantidade de passos ate E
e marcar o caminho com '*'. O grafo e implicito: nao e preciso montar a lista de adjacencia.
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main()
{
  vector<string> lab = {
    "##########",
    "#S...#...#",
    "#.##.#.#.#",
    "#.#..#.#.#",
    "#.#.##.#.#",
    "#...#..#E#",
    "###...##.#",
    "##########"};
  int L = lab.size(), C = lab[0].size();
  int sl = 0, sc = 0;
  for (int l = 0; l < L; l++) for (int c = 0; c < C; c++) if (lab[l][c] == 'S') { sl = l; sc = c; }

  vector<vector<int>> dist(L, vector<int>(C, -1));
  vector<vector<pair<int, int>>> pai(L, vector<pair<int, int>>(C, {-1, -1}));
  int dl[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
  queue<pair<int, int>> f;
  f.push({sl, sc}); dist[sl][sc] = 0;
  int el = -1, ec = -1;
  while (!f.empty()) {
    auto [l, c] = f.front(); f.pop();
    if (lab[l][c] == 'E') { el = l; ec = c; break; }
    for (int k = 0; k < 4; k++) {
      int nl = l + dl[k], nc = c + dc[k];
      if (lab[nl][nc] != '#' && dist[nl][nc] == -1) {   // a borda e parede, nao sai da matriz
        dist[nl][nc] = dist[l][c] + 1; pai[nl][nc] = {l, c}; f.push({nl, nc});
      }
    }
  }
  if (el < 0) { cout << "Sem saida" << endl; return 0; }
  for (auto p = pai[el][ec]; p.first != sl || p.second != sc; p = pai[p.first][p.second]) lab[p.first][p.second] = '*';
  for (auto &linha : lab) cout << linha << endl;
  cout << "Menor caminho: " << dist[el][ec] << " passos" << endl;
  return 0;
}
