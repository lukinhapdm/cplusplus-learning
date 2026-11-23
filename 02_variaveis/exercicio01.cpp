/*
Exercício 1. Média final ponderada de 3 notas (pesos 2, 1 e 3). Fazer teste de mesa.
*/
#include <iostream>
using namespace std;

int main()
{
  float n1, n2, n3, media;
  cout << "Digite as 3 notas: ";
  cin >> n1 >> n2 >> n3;
  // soma das notas multiplicadas pelos pesos, dividida pela soma dos pesos (2+1+3=6)
  media = (n1 * 2 + n2 * 1 + n3 * 3) / 6;
  cout << "Media final: " << media << endl;
  return 0;
}
