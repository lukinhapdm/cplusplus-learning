/*
Exercício 20. Função que recebe N >= 1 e calcula S = 1 + 1/2 + 1/3 + ... + 1/N.
*/
#include <iostream>
using namespace std;

float serie(int n)
{
  float s = 0;
  for (int i = 1; i <= n; i++) s += 1.0 / i;   // 1.0 evita divisao inteira
  return s;
}

int main()
{
  int n;
  do { cout << "N (>= 1): "; cin >> n; } while (n < 1);
  cout << "S = " << serie(n) << endl;
  return 0;
}
