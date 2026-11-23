/*
Exercicio 2. Sistema de pagamentos: classe abstrata Pagamento com processa(valor); derivadas Pix (sem taxa), Cartao (taxa 3%) e Boleto (taxa fixa R$2). Mostrar o valor final de cada.
*/
#include <iostream>
#include <string>
using namespace std;

class Pagamento {
public:
  virtual double processa(double v) const = 0;
  virtual string tipo() const = 0;
  virtual ~Pagamento() {}
};
class Pix : public Pagamento { public:
  double processa(double v) const override { return v; }
  string tipo() const override { return "Pix"; } };
class Cartao : public Pagamento { public:
  double processa(double v) const override { return v * 1.03; }
  string tipo() const override { return "Cartao"; } };
class Boleto : public Pagamento { public:
  double processa(double v) const override { return v + 2; }
  string tipo() const override { return "Boleto"; } };

int main()
{
  double valor;
  cout << "Valor da compra: "; cin >> valor;
  Pagamento *p[3] = {new Pix, new Cartao, new Boleto};
  for (Pagamento *x : p) { cout << x->tipo() << ": R$ " << x->processa(valor) << endl; delete x; }
  return 0;
}
