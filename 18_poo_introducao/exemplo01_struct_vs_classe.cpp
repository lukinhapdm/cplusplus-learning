/*
Exemplo 1. Da struct para a classe: dados e funcoes juntos, com encapsulamento.
*/
#include <iostream>
using namespace std;

// Estruturado: dados soltos e funcoes separadas
struct ContaS { float saldo; };
void depositaS(ContaS &c, float v) { c.saldo += v; }

// Orientado a objetos: a classe junta dados (atributos) e funcoes (metodos)
class Conta {
private:            // ninguem de fora mexe direto no saldo
  float saldo = 0;
public:             // so pelos metodos
  void deposita(float v) { if (v > 0) saldo += v; }
  bool saca(float v) { if (v > saldo) return false; saldo -= v; return true; }
  float getSaldo() { return saldo; }
};

int main()
{
  ContaS cs = {0};
  depositaS(cs, 100);
  cs.saldo = -999;   // nada impede um valor invalido

  Conta c;
  c.deposita(100);
  // c.saldo = -999;  // ERRO de compilacao: saldo e privado
  if (!c.saca(500)) cout << "Saldo insuficiente" << endl;
  cout << "Saldo: " << c.getSaldo() << endl;
  return 0;
}
