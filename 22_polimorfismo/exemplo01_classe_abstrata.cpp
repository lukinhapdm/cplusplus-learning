/*
Exemplo 1. Classe abstrata com funcao virtual pura e polimorfismo em um vetor de formas.
*/
#include <iostream>
#include <string>
using namespace std;

class Forma {
public:
  virtual double area() const = 0;      // virtual pura: obriga as filhas a implementar
  virtual string nome() const = 0;
  virtual ~Forma() {}
};

class Circulo : public Forma {
  double r;
public:
  Circulo(double r) : r(r) {}
  double area() const override { return 3.14159 * r * r; }
  string nome() const override { return "Circulo"; }
};

class Retangulo : public Forma {
  double b, h;
public:
  Retangulo(double b, double h) : b(b), h(h) {}
  double area() const override { return b * h; }
  string nome() const override { return "Retangulo"; }
};

int main()
{
  // Forma f;  // ERRO: classe abstrata nao pode ser instanciada
  Forma *formas[2] = {new Circulo(1), new Retangulo(2, 3)};
  for (Forma *f : formas) {
    cout << f->nome() << ": " << f->area() << endl;   // mesma chamada, comportamentos diferentes
    delete f;
  }
  return 0;
}
