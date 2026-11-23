/*
7.2.5 Exercício 3. Matriz m x n: mostrar elementos repetidos e quantas vezes.
*/
#include <iostream>
using namespace std;

const int MAX = 20;   // maximo de linhas e colunas

int main()
{
  int m, n;
  cout << "Linhas e colunas: "; cin >> m >> n;
  if (m > MAX) m = MAX;
  if (n > MAX) n = MAX;
  int mat[MAX][MAX], tot = m * n;
  for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> mat[i][j];
  // copia para um vetor para facilitar a contagem
  int v[MAX * MAX]; bool contado[MAX * MAX];
  for (int k = 0; k < tot; k++) { v[k] = mat[k / n][k % n]; contado[k] = false; }
  for (int k = 0; k < tot; k++) {
    if (contado[k]) continue;   // ja foi contado antes
    int qtd = 1;
    for (int p = k + 1; p < tot; p++)
      if (v[p] == v[k]) { qtd++; contado[p] = true; }
    if (qtd > 1) cout << v[k] << " aparece " << qtd << " vezes" << endl;
  }
  return 0;
}
