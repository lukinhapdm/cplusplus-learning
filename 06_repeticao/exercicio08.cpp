/*
Exercício 8. Ler N e depois N valores; para cada um mostrar valor e fatorial.
*/
#include <iostream>
using namespace std;

int main()
{
  int n, v;
  cout << "Quantos valores? "; cin >> n;
  for (int i = 1; i <= n; i++) {
    cout << "Valor: "; cin >> v;
    long long fat = 1;
    for (int j = 2; j <= v; j++) fat *= j;   // calcula o fatorial de v
    cout << v << " | " << fat << endl;
  }
  return 0;
}
