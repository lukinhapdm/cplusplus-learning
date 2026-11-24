/*
Exercicio 2. Distancia de edicao (Levenshtein): menor numero de insercoes, remocoes e substituicoes de
caracteres para transformar a em b.
  D[i][0] = i,  D[0][j] = j
  D[i][j] = min(D[i-1][j] + 1,                        remove a[i-1]
                D[i][j-1] + 1,                        insere b[j-1]
                D[i-1][j-1] + (a[i-1] != b[j-1]))     substitui (ou mantem se iguais)
Mostrar tambem a sequencia de operacoes, voltando pela tabela. Usado em corretores ortograficos.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void distancia(const string &a, const string &b)
{
  int n = a.size(), m = b.size();
  vector<vector<int>> D(n + 1, vector<int>(m + 1));
  for (int i = 0; i <= n; i++) D[i][0] = i;
  for (int j = 0; j <= m; j++) D[0][j] = j;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      D[i][j] = min({D[i - 1][j] + 1, D[i][j - 1] + 1, D[i - 1][j - 1] + (a[i - 1] != b[j - 1])});

  vector<string> ops;
  int i = n, j = m;
  while (i > 0 || j > 0) {
    if (i > 0 && j > 0 && D[i][j] == D[i - 1][j - 1] + (a[i - 1] != b[j - 1])) {
      if (a[i - 1] != b[j - 1]) ops.push_back(string("troca ") + a[i - 1] + " por " + b[j - 1]);
      i--; j--;
    } else if (i > 0 && D[i][j] == D[i - 1][j] + 1) { ops.push_back(string("remove ") + a[i - 1]); i--; }
    else { ops.push_back(string("insere ") + b[j - 1]); j--; }
  }
  reverse(ops.begin(), ops.end());
  cout << a << " -> " << b << ": distancia " << D[n][m] << " (";
  for (size_t k = 0; k < ops.size(); k++) cout << (k ? ", " : "") << ops[k];
  cout << ")" << endl;
}

int main()
{
  distancia("gato", "rato");
  distancia("domingo", "dominio");
  distancia("algoritmo", "logaritmo");
  distancia("casa", "cassada");
  return 0;
}
