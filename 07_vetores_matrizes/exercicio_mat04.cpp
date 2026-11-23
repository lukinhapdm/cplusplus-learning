/*
7.2.5 Exercício 4. somaDiagonal(matriz 5x5 float): soma da diagonal principal; testar.
*/
#include <iostream>
using namespace std;

float somaDiagonal(float m[5][5])
{
  float s = 0;
  for (int i = 0; i < 5; i++) s += m[i][i];   // diagonal principal: linha == coluna
  return s;
}

int main()
{
  float m[5][5];
  cout << "Preencha a matriz 5x5: ";
  for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) cin >> m[i][j];
  cout << "Soma da diagonal: " << somaDiagonal(m) << endl;
  return 0;
}
