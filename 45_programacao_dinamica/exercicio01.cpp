/*
Exercicio 1. Maior subsequencia comum (LCS) de duas cadeias (os caracteres nao precisam ser contiguos).
  L[i][j] = 0                              se i = 0 ou j = 0
          = L[i-1][j-1] + 1                se a[i-1] == b[j-1]
          = max(L[i-1][j], L[i][j-1])      caso contrario
Recuperar a subsequencia voltando pela tabela. Custo O(nm). Usado em diff de arquivos e bioinformatica.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string lcs(const string &a, const string &b)
{
  int n = a.size(), m = b.size();
  vector<vector<int>> L(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      L[i][j] = a[i - 1] == b[j - 1] ? L[i - 1][j - 1] + 1 : max(L[i - 1][j], L[i][j - 1]);

  string r;
  for (int i = n, j = m; i > 0 && j > 0;) {
    if (a[i - 1] == b[j - 1]) { r += a[i - 1]; i--; j--; }   // caractere faz parte da LCS
    else if (L[i - 1][j] >= L[i][j - 1]) i--;
    else j--;
  }
  reverse(r.begin(), r.end());
  return r;
}

int main()
{
  string pares[][2] = {{"ABCBDAB", "BDCABA"}, {"PROGRAMACAO", "PROGRESSAO"}, {"GATTACA", "TACGATACA"}};
  for (auto &p : pares) {
    string r = lcs(p[0], p[1]);
    cout << p[0] << " x " << p[1] << ": \"" << r << "\" (tamanho " << r.size() << ")" << endl;
  }
  return 0;
}
