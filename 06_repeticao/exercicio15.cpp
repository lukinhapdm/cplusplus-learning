/*
Exercício 15. Ler N inteiros positivos e mostrar o fatorial de cada (função fatorial).
*/
#include <iostream>
using namespace std;

long long fatorial(int n)
{
  long long f = 1;
  for (int i = 2; i <= n; i++) f *= i;
  return f;
}

int main()
{
  int n, v;
  cout << "Quantos numeros? "; cin >> n;
  for (int i = 1; i <= n; i++) {
    cout << "Numero: "; cin >> v;
    cout << v << "! = " << fatorial(v) << endl;
  }
  return 0;
}
