/*
7.2.5 Exercício 6. Preencher matriz m x n sem repetidos (avisar e descartar repetido).
*/
#include <iostream>
using namespace std;

int main()
{
  int m, n;
  cout << "Linhas e colunas: "; cin >> m >> n;
  int mat[m][n], qtd = 0;   // qtd = quantos ja foram inseridos
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) {
      int x; bool repetido;
      do {
        cout << "Elemento [" << i << "][" << j << "]: "; cin >> x;
        repetido = false;
        // compara so com os ja preenchidos
        for (int k = 0; k < qtd; k++)
          if (mat[k / n][k % n] == x) repetido = true;
        if (repetido) cout << "Valor ja existe, digite outro." << endl;
      } while (repetido);
      mat[i][j] = x; qtd++;
    }
  for (int i = 0; i < m; i++) { for (int j = 0; j < n; j++) cout << mat[i][j] << " "; cout << endl; }
  return 0;
}
