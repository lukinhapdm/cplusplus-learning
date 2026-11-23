/*
Exercicio 1. Classe base Veiculo (marca, ano) e derivadas Carro (portas) e Moto (cilindradas). Cada uma com metodo mostra.
*/
#include <iostream>
#include <string>
using namespace std;

class Veiculo {
protected:
  string marca;
  int ano;
public:
  Veiculo(string m, int a) : marca(m), ano(a) {}
  void mostraBase() const { cout << marca << " (" << ano << ")"; }
};

class Carro : public Veiculo {
  int portas;
public:
  Carro(string m, int a, int p) : Veiculo(m, a), portas(p) {}
  void mostra() const { mostraBase(); cout << " - " << portas << " portas" << endl; }
};

class Moto : public Veiculo {
  int cilindradas;
public:
  Moto(string m, int a, int c) : Veiculo(m, a), cilindradas(c) {}
  void mostra() const { mostraBase(); cout << " - " << cilindradas << " cc" << endl; }
};

int main()
{
  Carro c("Fiat", 2020, 4);
  Moto m("Honda", 2022, 160);
  c.mostra();
  m.mostra();
  return 0;
}
