/*
Exemplo 2. Funcoes virtuais: diferenca entre metodo comum e virtual quando usamos ponteiro da classe base; destrutor virtual.
*/
#include <iostream>
using namespace std;

class Base {
public:
  void comum() { cout << "Base::comum" << endl; }
  virtual void virt() { cout << "Base::virt" << endl; }
  virtual ~Base() { cout << "~Base" << endl; }   // virtual para destruir a filha corretamente
};

class Derivada : public Base {
public:
  void comum() { cout << "Derivada::comum" << endl; }
  void virt() override { cout << "Derivada::virt" << endl; }
  ~Derivada() { cout << "~Derivada" << endl; }
};

int main()
{
  Base *p = new Derivada;
  p->comum();   // Base::comum   -> decide pelo tipo do PONTEIRO
  p->virt();    // Derivada::virt -> decide pelo tipo do OBJETO
  delete p;     // chama ~Derivada e depois ~Base
  return 0;
}
