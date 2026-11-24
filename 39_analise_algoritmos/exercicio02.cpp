/*
Exercicio 2. Calcular x^n de duas formas e contar as multiplicacoes:
  (a) ingenua: x * x * ... * x                         -> n - 1 multiplicacoes, O(n)
  (b) recursiva por quadrados: x^n = (x^(n/2))^2, e mais um x se n for impar -> O(log n)
Mostra como a tecnica de projeto (dividir o problema pela metade) muda a ordem de custo.
*/
#include <iostream>
using namespace std;

long long mult;

long long potIngenua(long long x, int n)
{
  long long r = x;
  for (int i = 1; i < n; i++) { r *= x; mult++; }
  return r;
}

long long potRapida(long long x, int n)
{
  if (n == 1) return x;
  long long meia = potRapida(x, n / 2);   // uma unica chamada recursiva
  long long r = meia * meia; mult++;
  if (n % 2) { r *= x; mult++; }
  return r;
}

int main()
{
  for (int n : {10, 31, 32, 62}) {
    mult = 0; long long a = potIngenua(2, n); long long ma = mult;
    mult = 0; long long b = potRapida(2, n); long long mb = mult;
    cout << "2^" << n << " = " << b << (a == b ? "" : " (ERRO)") << ": ingenua " << ma << " mult., rapida " << mb << " mult." << endl;
  }
  return 0;
}
