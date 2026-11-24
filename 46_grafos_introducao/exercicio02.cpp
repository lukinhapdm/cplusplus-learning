/*
Exercicio 2. Potencias da matriz de adjacencia: o elemento (u, v) de A^k e o numero de passeios
(sequencias de arestas, podendo repetir vertices) de comprimento k entre u e v.
Consequencias: a diagonal de A^2 da o grau de cada vertice e traco(A^3) / 6 e o numero de triangulos.
Calcular para um grafo pequeno e conferir os triangulos contando todas as triplas.
*/
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<long long>> Matriz;

Matriz multiplica(const Matriz &A, const Matriz &B)
{
  int n = A.size();
  Matriz C(n, vector<long long>(n, 0));
  for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
      for (int j = 0; j < n; j++) C[i][j] += A[i][k] * B[k][j];
  return C;
}

void imprime(const char *nome, const Matriz &M)
{
  cout << nome << ":" << endl;
  for (auto &l : M) { cout << "  "; for (long long x : l) cout << x << " "; cout << endl; }
}

int main()
{
  Matriz A = {{0, 1, 1, 0, 0}, {1, 0, 1, 1, 0}, {1, 1, 0, 1, 1}, {0, 1, 1, 0, 1}, {0, 0, 1, 1, 0}};
  int n = A.size();
  Matriz A2 = multiplica(A, A), A3 = multiplica(A2, A);
  imprime("A^2 (diagonal = graus)", A2);
  imprime("A^3", A3);

  long long traco = 0;
  for (int i = 0; i < n; i++) traco += A3[i][i];
  int triangulos = 0;
  for (int a = 0; a < n; a++)
    for (int b = a + 1; b < n; b++)
      for (int c = b + 1; c < n; c++) if (A[a][b] && A[b][c] && A[a][c]) triangulos++;
  cout << "traco(A^3) / 6 = " << traco / 6 << ", triangulos contados = " << triangulos << endl;
  cout << "Passeios de comprimento 3 entre 0 e 4: " << A3[0][4] << endl;
  return 0;
}
