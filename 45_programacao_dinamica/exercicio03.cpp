/*
Exercicio 3. Multiplicacao de cadeia de matrizes: A1 A2 ... An, com Ai de dimensao d[i-1] x d[i].
A ordem dos parenteses nao muda o resultado, mas muda MUITO o numero de multiplicacoes escalares.
  M[i][i] = 0
  M[i][j] = min, para i <= k < j, de M[i][k] + M[k+1][j] + d[i-1] d[k] d[j]
S[i][j] guarda o k escolhido para imprimir a parentizacao otima. Custo O(n^3).
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<vector<long long>> M;
vector<vector<int>> S;

void imprime(int i, int j)
{
  if (i == j) { cout << "A" << i; return; }
  cout << "(";
  imprime(i, S[i][j]);
  imprime(S[i][j] + 1, j);
  cout << ")";
}

void resolve(const vector<int> &d)
{
  int n = d.size() - 1;
  M.assign(n + 1, vector<long long>(n + 1, 0));
  S.assign(n + 1, vector<int>(n + 1, 0));
  for (int tam = 2; tam <= n; tam++)          // tamanho da subcadeia: das menores para as maiores
    for (int i = 1; i + tam - 1 <= n; i++) {
      int j = i + tam - 1;
      M[i][j] = LLONG_MAX;
      for (int k = i; k < j; k++) {
        long long c = M[i][k] + M[k + 1][j] + (long long)d[i - 1] * d[k] * d[j];
        if (c < M[i][j]) { M[i][j] = c; S[i][j] = k; }
      }
    }
  long long esquerda = 0;   // custo de multiplicar da esquerda para a direita, para comparar
  for (int k = 2; k <= n; k++) esquerda += (long long)d[0] * d[k - 1] * d[k];
  cout << "Otimo: " << M[1][n] << " multiplicacoes com ";
  imprime(1, n);
  cout << "; esquerda para direita: " << esquerda << endl;
}

int main()
{
  resolve({10, 100, 5, 50});                 // A1 10x100, A2 100x5, A3 5x50
  resolve({30, 35, 15, 5, 10, 20, 25});      // exemplo classico (Cormen)
  return 0;
}
