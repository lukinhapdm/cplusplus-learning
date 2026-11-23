/*
Exercicio 3. Classe base Funcionario com metodo virtual calculaPagamento; derivadas Horista (horas x valor) e Mensalista (salario fixo). Calcular a folha usando um vetor de ponteiros da base.
*/
#include <iostream>
#include <string>
using namespace std;

class Funcionario {
protected:
  string nome;
public:
  Funcionario(string n) : nome(n) {}
  virtual double calculaPagamento() const { return 0; }
  string getNome() const { return nome; }
  virtual ~Funcionario() {}
};

class Horista : public Funcionario {
  double horas, valorHora;
public:
  Horista(string n, double h, double v) : Funcionario(n), horas(h), valorHora(v) {}
  double calculaPagamento() const override { return horas * valorHora; }
};

class Mensalista : public Funcionario {
  double salario;
public:
  Mensalista(string n, double s) : Funcionario(n), salario(s) {}
  double calculaPagamento() const override { return salario; }
};

int main()
{
  Funcionario *f[3] = {new Horista("Ana", 160, 25), new Mensalista("Bia", 5000), new Horista("Caio", 80, 30)};
  double total = 0;
  for (int i = 0; i < 3; i++) {
    double p = f[i]->calculaPagamento();   // chama a versao certa de cada um
    cout << f[i]->getNome() << ": " << p << endl;
    total += p;
    delete f[i];
  }
  cout << "Folha total: " << total << endl;
  return 0;
}
