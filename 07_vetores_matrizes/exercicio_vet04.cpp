/*
7.1.4 Exercício 4. Ler N valores, inverter o vetor e mostrá-lo.
*/
#include <iostream>
using namespace std;

int main()
{
  int n;
  cout << "Quantidade N: "; cin >> n;
  int v[n];
  for (int i = 0; i < n; i++) cin >> v[i];
  // troca o primeiro com o ultimo, o segundo com o penultimo... ate o meio
  for (int i = 0; i < n / 2; i++) {
    int aux = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = aux;
  }
  for (int i = 0; i < n; i++) cout << v[i] << " ";
  cout << endl;
  return 0;
}
