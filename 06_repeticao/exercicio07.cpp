/*
Exercício 7. Ler N e calcular E = 1 + 1/1! + 1/2! + ... + 1/N!.
*/
#include <iostream>
using namespace std;

int main()
{
  int n;
  double e = 1, fat = 1;
  do { cout << "N (positivo): "; cin >> n; } while (n <= 0);
  for (int i = 1; i <= n; i++) {
    fat = fat * i;     // aproveita o fatorial anterior: i! = (i-1)! * i
    e = e + 1 / fat;
  }
  cout << "E = " << e << endl;
  return 0;
}
