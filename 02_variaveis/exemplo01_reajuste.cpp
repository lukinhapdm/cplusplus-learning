#include <iostream>
using namespace std;

int main()
{
  float prod, aum, prod_reaj;
  cout << "Entre com o valor do produto: ";
  cin >> prod;
  aum = prod * 0.10;
  prod_reaj = prod + aum;
  cout << "Valor do aumento: " << aum << endl;
  cout << "Valor do produto reajustado: " << prod_reaj << endl;
  return 0;
}
