/*
Exercicio 4. TAD Matriz dinamica m x n: cria, preenche, imprime, calcula a transposta e libera.
*/
#include <iostream>
using namespace std;

// matriz dinamica = vetor de ponteiros, cada um apontando para uma linha
int **criaMatriz(int m, int n)
{
  int **mat = new int*[m];
  for (int i = 0; i < m; i++) mat[i] = new int[n];
  return mat;
}

void liberaMatriz(int **mat, int m)
{
  for (int i = 0; i < m; i++) delete[] mat[i];   // primeiro as linhas
  delete[] mat;                                  // depois o vetor de linhas
}

void imprime(int **mat, int m, int n)
{
  for (int i = 0; i < m; i++) { for (int j = 0; j < n; j++) cout << mat[i][j] << " "; cout << endl; }
}

// transposta: linha vira coluna (n x m)
int **transposta(int **mat, int m, int n)
{
  int **t = criaMatriz(n, m);
  for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) t[j][i] = mat[i][j];
  return t;
}

int main()
{
  int m, n;
  cout << "Linhas e colunas: "; cin >> m >> n;
  int **a = criaMatriz(m, n);
  for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  int **t = transposta(a, m, n);
  cout << "Transposta:" << endl;
  imprime(t, n, m);
  liberaMatriz(a, m);
  liberaMatriz(t, n);
  return 0;
}
