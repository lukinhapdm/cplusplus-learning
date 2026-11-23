/*
Exercício 1. Função que lê cargo e salário e retorna novo salário: Gerente 10%, Engenheiro 20%, Técnico 30%, outros 35%.
*/
#include <iostream>
#include <cstring>
using namespace std;

float novoSalario()
{
  char cargo[30]; float sal;
  cout << "Cargo: "; cin >> cargo;
  cout << "Salario: "; cin >> sal;
  // strcmp devolve 0 quando as strings sao iguais
  if (strcmp(cargo, "Gerente") == 0) return sal * 1.10;
  if (strcmp(cargo, "Engenheiro") == 0) return sal * 1.20;
  if (strcmp(cargo, "Tecnico") == 0) return sal * 1.30;
  return sal * 1.35;   // demais cargos
}

int main()
{
  cout << "Novo salario: " << novoSalario() << endl;
  return 0;
}
