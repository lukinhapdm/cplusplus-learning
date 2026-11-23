/*
Exercício 4. Raízes da equação de 2º grau a partir de a, b, c (usar sqrt de <cmath>). Fazer teste de mesa.
*/
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  float a, b, c, delta;
  cout << "Digite a, b e c: "; cin >> a >> b >> c;
  if (a == 0) { cout << "Nao e equacao do 2o grau" << endl; return 0; }
  delta = b * b - 4 * a * c;
  // o sinal de delta define quantas raizes reais existem
  if (delta < 0)
    cout << "Nao ha raizes reais" << endl;
  else if (delta == 0)
    cout << "Raiz unica: " << -b / (2 * a) << endl;
  else {
    cout << "x1 = " << (-b + sqrt(delta)) / (2 * a) << endl;
    cout << "x2 = " << (-b - sqrt(delta)) / (2 * a) << endl;
  }
  return 0;
}
