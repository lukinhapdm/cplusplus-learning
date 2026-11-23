/*
Exercício 1. Ímpares de 1 a 100 com for; refazer com while e do-while.
*/
#include <iostream>
using namespace std;

int main()
{
  // for: comeca em 1 e anda de 2 em 2 (so impares)
  for (int i = 1; i <= 100; i += 2) cout << i << " ";
  cout << endl;

  // while: mesma logica, controle manual do contador
  int i = 1;
  while (i <= 100) { cout << i << " "; i += 2; }
  cout << endl;

  // do-while: executa primeiro, testa depois
  i = 1;
  do { cout << i << " "; i += 2; } while (i <= 100);
  cout << endl;
  return 0;
}
