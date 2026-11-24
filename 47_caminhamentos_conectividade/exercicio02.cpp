/*
Exercicio 2. Isomorfismo: G e H sao isomorfos se existe uma bijecao f entre os vertices que preserva
adjacencia (u-v em G se e somente se f(u)-f(v) em H) - sao "o mesmo grafo desenhado diferente".
1) Invariantes: se n, m ou a sequencia de graus diferem, NAO sao isomorfos (mas iguais nao provam nada).
2) Busca da bijecao por backtracking, so associando vertices de mesmo grau e checando as arestas
   ja mapeadas a cada passo (poda).
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> Matriz;
Matriz G, H;
vector<int> f, gG, gH;
vector<bool> usadoH;
int n;

bool mapeia(int u)
{
  if (u == n) return true;
  for (int x = 0; x < n; x++) {
    if (usadoH[x] || gG[u] != gH[x]) continue;   // so vertices livres de mesmo grau
    bool ok = true;
    for (int v = 0; v < u && ok; v++) ok = G[u][v] == H[x][f[v]];   // arestas com os ja mapeados
    if (!ok) continue;
    f[u] = x; usadoH[x] = true;
    if (mapeia(u + 1)) return true;
    usadoH[x] = false;
  }
  return false;
}

void testa(const char *nome, const Matriz &a, const Matriz &b)
{
  G = a; H = b; n = G.size();
  cout << nome << ": ";
  if ((int)H.size() != n) { cout << "nao isomorfos (n diferente)" << endl; return; }
  gG.assign(n, 0); gH.assign(n, 0);
  for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) { gG[u] += G[u][v]; gH[u] += H[u][v]; }
  vector<int> sa = gG, sb = gH;
  sort(sa.begin(), sa.end()); sort(sb.begin(), sb.end());
  if (sa != sb) { cout << "nao isomorfos (sequencias de graus diferentes)" << endl; return; }
  f.assign(n, -1); usadoH.assign(n, false);
  if (mapeia(0)) {
    cout << "isomorfos, f = ";
    for (int u = 0; u < n; u++) cout << u << "->" << f[u] << " ";
    cout << endl;
  } else cout << "nao isomorfos (mesmos graus, mas nenhuma bijecao funciona)" << endl;
}

Matriz deArestas(int n, vector<pair<int, int>> e)
{
  Matriz M(n, vector<int>(n, 0));
  for (auto &a : e) M[a.first][a.second] = M[a.second][a.first] = 1;
  return M;
}

int main()
{
  // C6 desenhado de duas formas
  Matriz a = deArestas(6, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}});
  Matriz b = deArestas(6, {{0, 3}, {3, 1}, {1, 4}, {4, 2}, {2, 5}, {5, 0}});
  testa("C6 x C6 reordenado", a, b);
  // C6 x dois triangulos: ambos 2-regulares com 6 vertices, mas um e conexo e o outro nao
  Matriz c = deArestas(6, {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 3}});
  testa("C6 x 2 triangulos", a, c);
  // mesma sequencia de graus? nao: estrela x caminho
  Matriz d = deArestas(4, {{0, 1}, {0, 2}, {0, 3}}), e = deArestas(4, {{0, 1}, {1, 2}, {2, 3}});
  testa("Estrela x caminho", d, e);
  return 0;
}
