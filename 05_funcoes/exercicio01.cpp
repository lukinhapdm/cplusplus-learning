/*
Exercício 1. Função que recebe o ano e retorna true se bissexto (div. por 4 e não por 100, ou div. por 400).
*/
#include <iostream>
using namespace std;

// bissexto: divisivel por 4 e nao por 100, ou divisivel por 400
bool bissexto(int ano)
{
  return (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0;
}

int main()
{
  int ano;
  cout << "Ano: "; cin >> ano;
  if (bissexto(ano)) cout << "Bissexto" << endl;
  else cout << "Nao bissexto" << endl;
  return 0;
}
