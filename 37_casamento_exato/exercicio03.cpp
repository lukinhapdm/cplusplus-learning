/*
Exercicio 3. Shift-And aproximado: encontrar as posicoes em que o padrao ocorre com no maximo k erros
(insercao, remocao ou substituicao de um caractere). Usa k + 1 conjuntos R0..Rk; Rj guarda os prefixos
que casam com ate j erros. Com S(x) = (x << 1) | 1, ao ler o caractere c:
    R0' = S(R0) & M[c]
    Rj' = (S(Rj) & M[c])   casamento
        | Rj-1             insercao   (c sobra no texto)
        | S(Rj-1)          substituicao (c no lugar de P[i])
        | S(Rj-1')         remocao   (P[i] nao aparece no texto)
Inicialmente Rj = 2^j - 1 (os j primeiros caracteres podem ser "removidos").
O resultado e conferido com um algoritmo de programacao dinamica (distancia de edicao).
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long u64;

vector<int> shiftAndAproximado(const string &T, const string &P, int k)
{
  int m = P.size();
  u64 M[256] = {0};
  for (int j = 0; j < m; j++) M[(unsigned char)P[j]] |= 1ULL << j;
  vector<u64> R(k + 1);
  for (int j = 0; j <= k; j++) R[j] = (1ULL << j) - 1;
  u64 fim = 1ULL << (m - 1);
  vector<int> fins;
  for (int i = 0; i < (int)T.size(); i++) {
    u64 c = M[(unsigned char)T[i]];
    u64 anterior = R[0];                 // R[j-1] antes de ler c
    R[0] = ((R[0] << 1) | 1) & c;
    for (int j = 1; j <= k; j++) {
      u64 velho = R[j];
      R[j] = (((velho << 1) | 1) & c) | anterior | ((anterior << 1) | 1) | ((R[j - 1] << 1) | 1);
      anterior = velho;
    }
    if (R[k] & fim) fins.push_back(i);   // termina em i com ate k erros
  }
  return fins;
}

// conferencia: D[i] = menor distancia de edicao entre P e algum trecho do texto que termina em i
vector<int> programacaoDinamica(const string &T, const string &P, int k)
{
  int m = P.size();
  vector<int> col(m + 1), fins;
  for (int j = 0; j <= m; j++) col[j] = j;
  for (int i = 0; i < (int)T.size(); i++) {
    int diag = col[0];   // col[0] = 0: o casamento pode comecar em qualquer ponto
    for (int j = 1; j <= m; j++) {
      int tmp = col[j];
      col[j] = min({col[j] + 1, col[j - 1] + 1, diag + (P[j - 1] != T[i])});
      diag = tmp;
    }
    if (col[m] <= k) fins.push_back(i);
  }
  return fins;
}

int main()
{
  string T = "o testo do teste tinha um tste e um texte e um teeste";
  string P = "teste";
  for (int k = 0; k <= 2; k++) {
    vector<int> a = shiftAndAproximado(T, P, k), b = programacaoDinamica(T, P, k);
    cout << "k = " << k << ": termina em ";
    for (int x : a) cout << x << " ";
    cout << (a == b ? " (confere)" : " (DIFERENTE!)") << endl;
  }
  return 0;
}
