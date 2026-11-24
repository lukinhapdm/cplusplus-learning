/*
Exercicio 3. Subvetor de soma maxima por divisao e conquista: a melhor soma esta inteira na metade esquerda,
inteira na direita, ou cruza o meio (melhor sufixo da esquerda + melhor prefixo da direita, em O(n)).
T(n) = 2T(n/2) + n = O(n log n). Conferir com o algoritmo de Kadane, O(n).
Tambem encontrar o maximo de um vetor por D&C e mostrar que faz n - 1 comparacoes, como o iterativo.
*/
#include <iostream>
#include <climits>
#include <cstdlib>
using namespace std;

int somaMaxima(int v[], int ini, int fim)   // [ini, fim]
{
  if (ini == fim) return v[ini];
  int meio = (ini + fim) / 2;
  int esq = somaMaxima(v, ini, meio), dir = somaMaxima(v, meio + 1, fim);
  int s = 0, sufixo = INT_MIN, prefixo = INT_MIN;
  for (int i = meio; i >= ini; i--) { s += v[i]; if (s > sufixo) sufixo = s; }      // melhor terminando no meio
  s = 0;
  for (int i = meio + 1; i <= fim; i++) { s += v[i]; if (s > prefixo) prefixo = s; } // melhor comecando apos o meio
  return max(max(esq, dir), sufixo + prefixo);
}

int kadane(int v[], int n)
{
  int melhor = v[0], atual = v[0];
  for (int i = 1; i < n; i++) { atual = max(v[i], atual + v[i]); melhor = max(melhor, atual); }
  return melhor;
}

int compMax;
int maximo(int v[], int ini, int fim)
{
  if (ini == fim) return v[ini];
  int meio = (ini + fim) / 2;
  int a = maximo(v, ini, meio), b = maximo(v, meio + 1, fim);
  compMax++;
  return a > b ? a : b;
}

int main()
{
  int v[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  cout << "Exemplo: D&C = " << somaMaxima(v, 0, 8) << ", Kadane = " << kadane(v, 9) << " (subvetor 4 -1 2 1)" << endl;

  srand(1);
  int erros = 0;
  for (int t = 0; t < 1000; t++) {
    int n = 1 + rand() % 50, w[50];
    for (int i = 0; i < n; i++) w[i] = rand() % 21 - 10;
    if (somaMaxima(w, 0, n - 1) != kadane(w, n)) erros++;
  }
  cout << "1000 vetores aleatorios: " << erros << " diferencas" << endl;

  compMax = 0;
  cout << "Maximo do exemplo: " << maximo(v, 0, 8) << " com " << compMax << " comparacoes (n - 1 = 8)" << endl;
  return 0;
}
