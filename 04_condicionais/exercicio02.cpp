/*
Exercício 2. Contar quantas das 5 pessoas que trabalham ganham mais que o salário mínimo. Fazer teste de mesa.
*/
#include <iostream>
using namespace std;

int main()
{
  float minimo, s1, s2, s3, s4, s5;
  int cont = 0;   // quantos ganham mais que o minimo
  cout << "Salario minimo: "; cin >> minimo;
  cout << "Salarios das 5 pessoas: "; cin >> s1 >> s2 >> s3 >> s4 >> s5;
  // testa cada pessoa separadamente
  if (s1 > minimo) cont++;
  if (s2 > minimo) cont++;
  if (s3 > minimo) cont++;
  if (s4 > minimo) cont++;
  if (s5 > minimo) cont++;
  cout << cont << " pessoa(s) ganham mais que o minimo" << endl;
  return 0;
}
