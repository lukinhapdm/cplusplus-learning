/*
Exercicio 2. Resolver um Sudoku 9x9 com backtracking: procura a proxima casa vazia, tenta os digitos
1..9 que nao aparecem na linha, na coluna nem no bloco 3x3, e volta se nenhum servir.
*/
#include <iostream>
using namespace std;

int g[9][9] = {
  {5, 3, 0, 0, 7, 0, 0, 0, 0},
  {6, 0, 0, 1, 9, 5, 0, 0, 0},
  {0, 9, 8, 0, 0, 0, 0, 6, 0},
  {8, 0, 0, 0, 6, 0, 0, 0, 3},
  {4, 0, 0, 8, 0, 3, 0, 0, 1},
  {7, 0, 0, 0, 2, 0, 0, 0, 6},
  {0, 6, 0, 0, 0, 0, 2, 8, 0},
  {0, 0, 0, 4, 1, 9, 0, 0, 5},
  {0, 0, 0, 0, 8, 0, 0, 7, 9}};
long long tentativas = 0;

bool pode(int l, int c, int d)
{
  for (int i = 0; i < 9; i++) if (g[l][i] == d || g[i][c] == d) return false;
  int bl = l / 3 * 3, bc = c / 3 * 3;   // canto do bloco 3x3
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (g[bl + i][bc + j] == d) return false;
  return true;
}

bool resolve()
{
  for (int l = 0; l < 9; l++)
    for (int c = 0; c < 9; c++)
      if (g[l][c] == 0) {   // primeira casa vazia
        for (int d = 1; d <= 9; d++)
          if (pode(l, c, d)) {
            tentativas++;
            g[l][c] = d;
            if (resolve()) return true;
            g[l][c] = 0;     // backtrack
          }
        return false;        // nenhum digito serve: volta
      }
  return true;               // nenhuma casa vazia: resolvido
}

int main()
{
  if (resolve()) {
    for (int l = 0; l < 9; l++) {
      for (int c = 0; c < 9; c++) cout << g[l][c] << (c % 3 == 2 && c < 8 ? " | " : " ");
      cout << endl;
      if (l % 3 == 2 && l < 8) cout << "------+-------+------" << endl;
    }
    cout << tentativas << " digitos colocados durante a busca" << endl;
  } else cout << "Sem solucao" << endl;
  return 0;
}
