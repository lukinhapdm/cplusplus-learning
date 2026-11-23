/*
Exercício 2. Função que recebe um float e retorna, por referência, a parte inteira e a parte decimal.
*/
#include <iostream>
using namespace std;

// inteira e decimal sao por referencia (&): a funcao altera as variaveis do main
void separa(float num, int &inteira, float &decimal)
{
  inteira = (int) num;          // corta a parte depois da virgula
  decimal = num - inteira;      // o que sobrou
}

int main()
{
  float n, d; int i;
  cout << "Numero: "; cin >> n;
  separa(n, i, d);
  cout << "Parte inteira: " << i << " | Parte decimal: " << d << endl;
  return 0;
}
