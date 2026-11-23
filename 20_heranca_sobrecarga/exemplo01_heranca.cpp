/*
Exemplo 1. Heranca: classe base Pessoa e derivadas Aluno e Professor, com construtor da base e protected.
*/
#include <iostream>
#include <string>
using namespace std;

class Pessoa {
protected:              // filhas podem acessar
  string nome;
  int idade;
public:
  Pessoa(string n, int i) : nome(n), idade(i) {}
  void apresenta() const { cout << nome << ", " << idade << " anos" << endl; }
};

class Aluno : public Pessoa {   // Aluno herda tudo de Pessoa
private:
  string curso;
public:
  Aluno(string n, int i, string c) : Pessoa(n, i), curso(c) {}   // chama o construtor da base
  void mostra() const { apresenta(); cout << "  Curso: " << curso << endl; }
};

class Professor : public Pessoa {
private:
  double salario;
public:
  Professor(string n, int i, double s) : Pessoa(n, i), salario(s) {}
  void mostra() const { apresenta(); cout << "  Salario: " << salario << endl; }
};

int main()
{
  Aluno a("Ana", 20, "Computacao");
  Professor p("Carlos", 45, 8000);
  a.mostra();
  p.mostra();
  return 0;
}
