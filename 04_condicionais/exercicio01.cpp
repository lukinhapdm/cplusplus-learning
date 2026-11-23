/*
Exercício 1. Verificar se funcionário é bem ou mal remunerado (limite R$5.000,00). Fazer teste de mesa.
*/
#include <iostream>
using namespace std;

int main()
{
  float salario;
  cout << "Salario: "; cin >> salario;
  // acima de 5000 e considerado bem remunerado
  if (salario > 5000) cout << "Bem remunerado" << endl;
  else cout << "Mal remunerado" << endl;
  return 0;
}
