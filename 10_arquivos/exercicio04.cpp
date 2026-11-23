/*
Exercício 4. Alterar 10.2.3 para gravar o nome completo do funcionário.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Funcionario {
  int codigo;
  string nome;   // nome completo (com espacos)
  float salario;
};

// um campo por linha; o nome fica inteiro na sua linha
void grava(string arq, Funcionario f)
{
  ofstream out(arq);
  out << f.codigo << endl << f.nome << endl << f.salario << endl;
  out.close();
}

int main()
{
  Funcionario f;
  cout << "Codigo: "; cin >> f.codigo;
  cout << "Nome completo: "; cin.ignore(); getline(cin, f.nome);   // getline le com espacos
  cout << "Salario: "; cin >> f.salario;
  grava("funcionario.txt", f);
  return 0;
}
