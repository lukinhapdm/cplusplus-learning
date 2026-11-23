/*
7.2.5 Exercício 5. inverteDiagonal(matriz 5x5): trocar diagonal principal pela secundária; testar.
*/
#include <iostream>
using namespace std;

void inverteDiagonal(float m[5][5])
{
  // diagonal secundaria: coluna = 4 - linha
  for (int i = 0; i < 5; i++) {
    float aux = m[i][i];
    m[i][i] = m[i][4 - i];
    m[i][4 - i] = aux;
  }
}

int main()
{
  float m[5][5];
  cout << "Preencha a matriz 5x5: ";
  for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) cin >> m[i][j];
  inverteDiagonal(m);
  for (int i = 0; i < 5; i++) { for (int j = 0; j < 5; j++) cout << m[i][j] << " "; cout << endl; }
  return 0;
}
