/*
7.2.5 Exercício 7. A(4x3) x B(3x4) = C(4x4); mostrar C.
*/
#include <iostream>
using namespace std;

int main()
{
  float a[4][3], b[3][4], c[4][4];
  cout << "Matriz A (4x3): "; for (int i = 0; i < 4; i++) for (int j = 0; j < 3; j++) cin >> a[i][j];
  cout << "Matriz B (3x4): "; for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) cin >> b[i][j];
  // c[i][j] = soma de (linha i de A) x (coluna j de B)
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      c[i][j] = 0;
      for (int k = 0; k < 3; k++) c[i][j] += a[i][k] * b[k][j];
    }
  for (int i = 0; i < 4; i++) { for (int j = 0; j < 4; j++) cout << c[i][j] << " "; cout << endl; }
  return 0;
}
