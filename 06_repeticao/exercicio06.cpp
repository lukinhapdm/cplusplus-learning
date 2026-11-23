/*
Exercício 6. Mostrar apenas o n-ésimo termo de Fibonacci.
*/
#include <iostream>
using namespace std;

int main()
{
  int n, a = 0, b = 1, c;
  cout << "n: "; cin >> n;
  // avanca a serie sem imprimir; b guarda o termo atual
  for (int i = 2; i <= n; i++) { c = a + b; a = b; b = c; }
  cout << "Termo " << n << ": " << b << endl;
  return 0;
}
