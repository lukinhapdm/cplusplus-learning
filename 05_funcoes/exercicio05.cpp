/*
Exercício 5. Função maior3 que recebe 3 inteiros e, usando maior, retorna o maior.
*/
#include <iostream>
using namespace std;

int maior(int a, int b)
{
  if (a > b) return a;
  return b;
}

// reaproveita maior(): maior entre a e b, depois compara com c
int maior3(int a, int b, int c)
{
  return maior(maior(a, b), c);
}

int main()
{
  int x, y, z;
  cout << "Tres inteiros: "; cin >> x >> y >> z;
  cout << "Maior: " << maior3(x, y, z) << endl;
  return 0;
}
