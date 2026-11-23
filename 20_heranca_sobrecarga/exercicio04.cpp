/*
Exercicio 4. Heranca em niveis: Funcionario -> Gerente -> Diretor. Cada nivel acrescenta um bonus sobre o salario do nivel anterior (redefinindo o metodo salarioFinal).
*/
#include <iostream>
#include <string>
using namespace std;

class Funcionario {
protected:
  string nome;
  double base;
public:
  Funcionario(string n, double b) : nome(n), base(b) {}
  double salarioFinal() const { return base; }
};

class Gerente : public Funcionario {
public:
  Gerente(string n, double b) : Funcionario(n, b) {}
  // redefine: salario do funcionario + 20%
  double salarioFinal() const { return Funcionario::salarioFinal() * 1.2; }
};

class Diretor : public Gerente {
public:
  Diretor(string n, double b) : Gerente(n, b) {}
  // salario do gerente + 3000 fixo
  double salarioFinal() const { return Gerente::salarioFinal() + 3000; }
};

int main()
{
  Funcionario f("Ana", 3000);
  Gerente g("Bia", 3000);
  Diretor d("Caio", 3000);
  cout << f.salarioFinal() << " " << g.salarioFinal() << " " << d.salarioFinal() << endl;   // 3000 3600 6600
  return 0;
}
