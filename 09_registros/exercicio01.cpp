/*
Exercício 1. Struct conta (número, cliente, saldo): ler e exibir uma conta (modular).
*/
#include <iostream>
#include <string>
using namespace std;

struct Conta {
  int numero;
  string cliente;
  float saldo;
};

// por referencia para preencher a conta do main
void le(Conta &c)
{
  cout << "Numero: "; cin >> c.numero;
  cout << "Cliente: "; cin.ignore(); getline(cin, c.cliente);
  cout << "Saldo: "; cin >> c.saldo;
}

void exibe(Conta c)
{
  cout << c.numero << " | " << c.cliente << " | " << c.saldo << endl;
}

int main()
{
  Conta c;
  le(c);
  exibe(c);
  return 0;
}
