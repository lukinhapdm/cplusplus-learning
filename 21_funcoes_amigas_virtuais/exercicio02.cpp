/*
Exercicio 2. Classes Conta e Banco, onde Banco e classe amiga de Conta e pode aplicar juros diretamente no saldo privado.
*/
#include <iostream>
#include <string>
using namespace std;

class Conta {
  string titular;
  double saldo;
public:
  Conta(string t, double s) : titular(t), saldo(s) {}
  void mostra() const { cout << titular << ": R$ " << saldo << endl; }
  friend class Banco;   // so o Banco mexe no saldo direto
};

class Banco {
public:
  void aplicaJuros(Conta &c, double taxa) { c.saldo += c.saldo * taxa / 100; }
};

int main()
{
  Conta c("Ana", 1000);
  Banco b;
  b.aplicaJuros(c, 5);
  c.mostra();   // 1050
  return 0;
}
