/*
Exercicio 2. Caminhos mais curtos entre TODOS os pares: algoritmo de Floyd-Warshall (programacao dinamica).
D[k][i][j] = menor caminho de i a j usando so os vertices 0..k como intermediarios:
  D[i][j] = min(D[i][j], D[i][k] + D[k][j]), para k = 0..n-1 (a tabela pode ser atualizada no lugar).
prox[i][j] guarda o proximo vertice do caminho para reconstrui-lo. Custo O(n^3). Aceita pesos negativos
(sem ciclos negativos; um D[i][i] < 0 no final indica ciclo negativo).
*/
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const int INF = 1000000000;

int main()
{
  int n = 5;
  vector<vector<int>> D(n, vector<int>(n, INF)), prox(n, vector<int>(n, -1));
  int arcos[][3] = {{0, 1, 3}, {0, 2, 8}, {0, 4, -4}, {1, 3, 1}, {1, 4, 7}, {2, 1, 4}, {3, 0, 2}, {3, 2, -5}, {4, 3, 6}};
  for (int i = 0; i < n; i++) { D[i][i] = 0; prox[i][i] = i; }
  for (auto &a : arcos) { D[a[0]][a[1]] = a[2]; prox[a[0]][a[1]] = a[1]; }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (D[i][k] < INF && D[k][j] < INF && D[i][k] + D[k][j] < D[i][j]) {
          D[i][j] = D[i][k] + D[k][j];
          prox[i][j] = prox[i][k];   // para ir de i a j, comeca indo para onde se vai de i a k
        }

  cout << "Distancias:" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) printf("%5d", D[i][j]);
    printf("\n");
  }
  for (auto par : {make_pair(0, 2), make_pair(4, 1), make_pair(2, 4)}) {
    int i = par.first, j = par.second;
    cout << "Caminho " << i << " -> " << j << " (custo " << D[i][j] << "): " << i;
    while (i != j) { i = prox[i][j]; cout << " -> " << i; }
    cout << endl;
  }
  return 0;
}
