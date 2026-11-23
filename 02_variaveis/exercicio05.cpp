/*
Exercício 5. Caminhão de lenha vendido por X reais; custo = 4/5 do preço (usar constante). Calcular o lucro.
*/
#include <iostream>
using namespace std;

int main()
{
  const float CUSTO = 4.0 / 5.0;   // custo = 4/5 do preco
  float x, lucro;
  cout << "Preco de venda do caminhao de lenha: "; cin >> x;
  lucro = x - x * CUSTO;   // lucro = venda - custo
  cout << "Lucro: " << lucro << endl;
  return 0;
}
