/*
Exemplo 1. Funcao amiga (friend) e classe amiga: acessam membros privados sem ser metodo da classe.
*/
#include <iostream>
using namespace std;

class Caixa;   // declaracao antecipada

class Inspetor {
public:
  void verifica(const Caixa &c);
};

class Caixa {
private:
  double largura;
public:
  Caixa(double l) : largura(l) {}
  friend double dobro(const Caixa &c);   // funcao amiga
  friend class Inspetor;                  // classe amiga: todos os metodos dela tem acesso
};

double dobro(const Caixa &c) { return c.largura * 2; }   // acessa o privado direto
void Inspetor::verifica(const Caixa &c) { cout << "Largura: " << c.largura << endl; }

int main()
{
  Caixa c(5);
  cout << "Dobro: " << dobro(c) << endl;
  Inspetor i;
  i.verifica(c);
  return 0;
}
