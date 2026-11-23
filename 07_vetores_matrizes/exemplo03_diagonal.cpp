#include <iostream>
using namespace std;

int main()
{
  int mat[3][3], s = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    { cout << "Insira o elemento da " << i+1 << "ª linha, " << j+1 << "ª coluna: "; cin >> mat[i][j]; }
  for (int i = 0; i < 3; i++) s += mat[i][i];
  cout << "Soma dos elementos da diagonal principal = " << s << endl;
}
