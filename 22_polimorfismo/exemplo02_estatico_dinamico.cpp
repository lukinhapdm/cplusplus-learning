/*
Exemplo 2. Polimorfismo estatico (sobrecarga, decidido na compilacao) x dinamico (virtual, decidido na execucao) e uso de referencia.
*/
#include <iostream>
using namespace std;

// estatico: o compilador escolhe pela assinatura
void imprime(int x) { cout << "int: " << x << endl; }
void imprime(double x) { cout << "double: " << x << endl; }

// dinamico: escolhido em tempo de execucao pelo objeto real
class Instrumento {
public:
  virtual void toca() const { cout << "..." << endl; }
  virtual ~Instrumento() {}
};
class Violao : public Instrumento { public: void toca() const override { cout << "Plim plim" << endl; } };
class Bateria : public Instrumento { public: void toca() const override { cout << "Tum tum" << endl; } };

// recebe qualquer Instrumento por referencia
void apresentacao(const Instrumento &i) { i.toca(); }

int main()
{
  imprime(5); imprime(5.5);
  Violao v; Bateria b;
  apresentacao(v);
  apresentacao(b);
  return 0;
}
