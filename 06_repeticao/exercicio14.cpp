/*
Exercício 14. Ler 10 inteiros e contar os primos, usando função ehPrimo.
*/
#include <iostream>
using namespace std;

// primo: maior que 1 e sem divisores entre 2 e n-1
bool ehPrimo(int n)
{
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++)   // basta testar ate a raiz de n
    if (n % i == 0) return false;
  return true;
}

int main()
{
  int n, primos = 0;
  for (int i = 1; i <= 10; i++) {
    cout << "Numero " << i << ": "; cin >> n;
    if (ehPrimo(n)) primos++;
  }
  cout << "Quantidade de primos: " << primos << endl;
  return 0;
}
