/*
Exercicio 4. Usar dynamic_cast para identificar, em um vetor de Veiculo*, quais sao Caminhoes e mostrar a carga deles.
*/
#include <iostream>
using namespace std;

class Veiculo {
public:
  virtual void descreve() const { cout << "Veiculo" << endl; }
  virtual ~Veiculo() {}
};
class Carro : public Veiculo { public: void descreve() const override { cout << "Carro" << endl; } };
class Caminhao : public Veiculo {
  double carga;
public:
  Caminhao(double c) : carga(c) {}
  void descreve() const override { cout << "Caminhao" << endl; }
  double getCarga() const { return carga; }
};

int main()
{
  Veiculo *v[3] = {new Carro, new Caminhao(12.5), new Caminhao(8)};
  for (Veiculo *x : v) {
    x->descreve();
    // dynamic_cast devolve nullptr se o objeto nao for Caminhao
    if (Caminhao *c = dynamic_cast<Caminhao*>(x)) cout << "  Carga: " << c->getCarga() << " t" << endl;
    delete x;
  }
  return 0;
}
