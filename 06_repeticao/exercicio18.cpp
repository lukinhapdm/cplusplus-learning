/*
Exercício 18. Sub-rotina peso ideal: homens 72.7*alt-58; mulheres 62.1*alt-44.7.
*/
#include <iostream>
using namespace std;

float pesoIdeal(float alt, char sexo)
{
  if (sexo == 'm' || sexo == 'M') return 72.7 * alt - 58;   // homens
  return 62.1 * alt - 44.7;                                // mulheres
}

int main()
{
  float alt; char sexo;
  cout << "Altura e sexo (m/f): "; cin >> alt >> sexo;
  cout << "Peso ideal: " << pesoIdeal(alt, sexo) << endl;
  return 0;
}
