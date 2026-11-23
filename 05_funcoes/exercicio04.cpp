/*
Exercício 4. Função maior que recebe 2 inteiros e retorna o maior.
*/
#include <iostream>
using namespace std;

int maior(int a, int b)
{
  if (a > b) return a;
  return b;
}

int main()
{
  int x, y;
  cout << "Dois inteiros: "; cin >> x >> y;
  cout << "Maior: " << maior(x, y) << endl;
  return 0;
}
