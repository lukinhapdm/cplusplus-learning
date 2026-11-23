/*
Exercício 10. Calcular x^y sem funções pré-definidas.
*/
#include <iostream>
using namespace std;

int main()
{
  double x, r = 1;
  int y;
  cout << "x e y: "; cin >> x >> y;
  // x^y = x multiplicado por ele mesmo y vezes
  for (int i = 1; i <= (y < 0 ? -y : y); i++) r *= x;
  if (y < 0) r = 1 / r;   // expoente negativo inverte o resultado
  cout << x << "^" << y << " = " << r << endl;
  return 0;
}
