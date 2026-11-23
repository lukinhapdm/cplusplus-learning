/*
Exercício 4. Ler um inteiro e mostrar sua tabuada.
*/
#include <iostream>
using namespace std;

int main()
{
  int n;
  cout << "Numero: "; cin >> n;
  // multiplica n por 1 ate 10
  for (int i = 1; i <= 10; i++)
    cout << n << " x " << i << " = " << n * i << endl;
  return 0;
}
