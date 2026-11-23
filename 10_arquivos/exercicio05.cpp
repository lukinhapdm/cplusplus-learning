/*
Exercício 5. Alterar 10.2.4 para ler o nome completo do funcionário.
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

// le na mesma ordem em que foi gravado
bool le(string arq, Funcionario &f)
{
  ifstream in(arq);
  if (!in) return false;
  in >> f.codigo;
  in.ignore();              // descarta o '\n' que sobrou depois do numero
  getline(in, f.nome);      // nome completo
  in >> f.salario;
  in.close();
  return true;
}

int main()
{
  Funcionario f;
  if (le("funcionario.txt", f))
    cout << f.codigo << " | " << f.nome << " | " << f.salario << endl;
  else cout << "Arquivo nao encontrado" << endl;
  return 0;
}
