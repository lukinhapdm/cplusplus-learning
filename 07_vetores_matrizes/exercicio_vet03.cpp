/*
7.1.4 Exercício 3. Vetor de 10 com valores validados em [0,9]: maior elemento e vetor dividido pelo maior.
*/
#include <iostream>
using namespace std;

int main()
{
  int v[10], maior;
  for (int i = 0; i < 10; i++) {
    // repete a leitura ate o valor estar entre 0 e 9
    do { cout << "Valor " << i + 1 << " [0-9]: "; cin >> v[i]; } while (v[i] < 0 || v[i] > 9);
  }
  maior = v[0];
  for (int i = 1; i < 10; i++) if (v[i] > maior) maior = v[i];
  cout << "Maior: " << maior << endl;
  if (maior == 0) { cout << "Nao da para dividir por zero" << endl; return 0; }
  cout << "Vetor dividido pelo maior: ";
  for (int i = 0; i < 10; i++) cout << (float) v[i] / maior << " ";
  cout << endl;
  return 0;
}
