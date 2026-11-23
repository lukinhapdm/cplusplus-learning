#include <iostream>
using namespace std;

void multiplica(float mat[5][5], float k)
{ for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) mat[i][j] = k * mat[i][j]; }
int main()
{
  float k, valores[5][5];
  cout << "Preencha os valores da matriz:" << endl;
  for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j)
  { cout << "Elemento [" << i << "][" << j << "]: "; cin >> valores[i][j]; }
  cout << "Digite o valor de uma constante k: "; cin >> k;
  multiplica(valores, k);
  for (int i = 0; i < 5; ++i) { for (int j = 0; j < 5; ++j) cout << valores[i][j] << " "; cout << endl; }
}
