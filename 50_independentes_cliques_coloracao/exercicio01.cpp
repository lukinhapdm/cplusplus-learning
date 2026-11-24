/*
Exercicio 1. Listar todas as cliques MAXIMAIS (que nao cabem dentro de uma clique maior) com o algoritmo de
Bron-Kerbosch com pivo. Mantem tres conjuntos: R (clique atual), P (candidatos que podem entrar) e
X (ja processados, para nao repetir). R e maximal quando P e X ficam vazios. O pivo u (de P ou X com mais
vizinhos em P) evita explorar ramos que gerariam as mesmas cliques: so tenta os vertices de P fora de N(u).
*/
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<unsigned> adj;
int chamadas = 0;

void bronKerbosch(unsigned R, unsigned P, unsigned X)
{
  chamadas++;
  if (!P && !X) {
    cout << "  {";
    for (int u = 0; u < n; u++) if (R >> u & 1) cout << " " << u;
    cout << " }" << endl;
    return;
  }
  int pivo = -1, melhor = -1;
  for (int u = 0; u < n; u++)
    if (((P | X) >> u & 1) && __builtin_popcount(P & adj[u]) > melhor) { melhor = __builtin_popcount(P & adj[u]); pivo = u; }
  unsigned candidatos = P & ~adj[pivo];
  for (int v = 0; v < n; v++)
    if (candidatos >> v & 1) {
      bronKerbosch(R | (1u << v), P & adj[v], X & adj[v]);
      P &= ~(1u << v);   // v ja processado: sai de P e vai para X
      X |= 1u << v;
    }
}

int main()
{
  n = 9;
  adj.assign(n, 0);
  int e[][2] = {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {0, 3}, {3, 4}, {4, 5}, {5, 6}, {4, 6}, {6, 7}, {7, 8}, {6, 8}};
  for (auto &a : e) { adj[a[0]] |= 1u << a[1]; adj[a[1]] |= 1u << a[0]; }
  cout << "Cliques maximais:" << endl;
  bronKerbosch(0, (1u << n) - 1, 0);
  cout << "(" << chamadas << " chamadas)" << endl;
  return 0;
}
