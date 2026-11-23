/*
Exercício 3. Salário depositado, dois cheques emitidos; CPMF de 0,38% por retirada (usar constante). Calcular saldo atual.
*/
#include <iostream>
using namespace std;

// Vantagem da constante: o valor fica em um so lugar e nao pode ser alterado por engano.
int main()
{
  const float CPMF = 0.0038;   // 0,38%
  float saldo = 0, salario, ch1, ch2;
  cout << "Salario depositado: "; cin >> salario;
  cout << "Valor dos dois cheques: "; cin >> ch1 >> ch2;
  saldo = saldo + salario;
  // cada cheque e uma retirada: desconta o valor + a CPMF sobre ele
  saldo = saldo - ch1 - ch1 * CPMF;
  saldo = saldo - ch2 - ch2 * CPMF;
  cout << "Saldo atual: " << saldo << endl;
  return 0;
}
