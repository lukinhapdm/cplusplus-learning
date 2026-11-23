/*
Exercício 5. Tabela de conversão de 1 a 20 polegadas para cm (1 pol = 2,54 cm).
*/
#include <iostream>
using namespace std;

int main()
{
  cout << "Polegadas | Centimetros" << endl;
  for (int p = 1; p <= 20; p++)
    cout << p << " | " << p * 2.54 << endl;   // 1 pol = 2,54 cm
  return 0;
}
