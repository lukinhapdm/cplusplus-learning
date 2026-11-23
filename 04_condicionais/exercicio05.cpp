/*
Exercício 5. Dados 3 inteiros, exibi-los em ordem crescente. Fazer teste de mesa.
*/
#include <iostream>
using namespace std;

int main()
{
  int a, b, c, aux;
  cout << "Digite 3 inteiros: "; cin >> a >> b >> c;
  // troca os valores de lugar ate ficar a <= b <= c
  if (a > b) { aux = a; a = b; b = aux; }
  if (a > c) { aux = a; a = c; c = aux; }
  if (b > c) { aux = b; b = c; c = aux; }
  cout << a << " " << b << " " << c << endl;
  return 0;
}
