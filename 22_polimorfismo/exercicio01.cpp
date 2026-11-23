/*
Exercicio 1. Classe abstrata Animal (som, movimento) com Cachorro, Passaro e Peixe. Percorrer um vetor de Animal* chamando os metodos.
*/
#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
  virtual string som() const = 0;
  virtual string movimento() const = 0;
  virtual ~Animal() {}
};
class Cachorro : public Animal { public:
  string som() const override { return "Au au"; }
  string movimento() const override { return "corre"; } };
class Passaro : public Animal { public:
  string som() const override { return "Piu piu"; }
  string movimento() const override { return "voa"; } };
class Peixe : public Animal { public:
  string som() const override { return "(silencio)"; }
  string movimento() const override { return "nada"; } };

int main()
{
  Animal *a[3] = {new Cachorro, new Passaro, new Peixe};
  for (Animal *x : a) { cout << x->som() << " e " << x->movimento() << endl; delete x; }
  return 0;
}
