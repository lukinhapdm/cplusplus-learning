/*
Exercicio 1. Classe ContaBancaria com titular, numero e saldo; construtor; deposito, saque (sem saldo negativo) e extrato.
*/
#include <iostream>
#include <string>
using namespace std;

class ContaBancaria {
private:
  string titular;
  int numero;
  double saldo;
public:
  ContaBancaria(string t, int n, double s = 0) : titular(t), numero(n), saldo(s) {}
  void deposita(double v) { if (v > 0) saldo += v; }
  bool saca(double v)
  {
    if (v <= 0 || v > saldo) return false;   // nao deixa negativo
    saldo -= v;
    return true;
  }
  void extrato() const { cout << numero << " | " << titular << " | R$ " << saldo << endl; }
};

int main()
{
  ContaBancaria c("Ana", 123, 100);
  c.deposita(50);
  if (!c.saca(500)) cout << "Saque negado" << endl;
  c.saca(30);
  c.extrato();   // 120
  return 0;
}
