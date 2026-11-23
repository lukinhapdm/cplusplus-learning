/*
Exercício 2. Receber salário bruto e percentual de imposto; calcular imposto e salário líquido.
*/
#include <iostream>
using namespace std;

int main()
{
  float bruto, perc, imposto, liquido;
  cout << "Salario bruto: "; cin >> bruto;
  cout << "Percentual de imposto (%): "; cin >> perc;
  imposto = bruto * perc / 100;   // valor do imposto
  liquido = bruto - imposto;      // o que sobra para o funcionario
  cout << "Imposto: " << imposto << endl;
  cout << "Salario liquido: " << liquido << endl;
  return 0;
}
