/*
Exercício 5. Função que verifica se palavra é palíndromo (AMA, ASA, SOLOS, ARARA).
*/
#include <iostream>
#include <cstring>
using namespace std;

// compara a primeira letra com a ultima, a segunda com a penultima...
bool palindromo(const char p[])
{
  int n = strlen(p);
  for (int i = 0; i < n / 2; i++)
    if (p[i] != p[n - 1 - i]) return false;
  return true;
}

int main()
{
  char p[50];
  cout << "Palavra: "; cin >> p;
  cout << (palindromo(p) ? "E palindromo" : "Nao e palindromo") << endl;
  return 0;
}
