/*
Exercicio 1. Revisao de fatos matematicos usados na analise: conferir numericamente
  (a) soma de i, para i = 1..n          = n(n+1)/2
  (b) soma de i^2                       = n(n+1)(2n+1)/6
  (c) soma de 2^i, para i = 0..k        = 2^(k+1) - 1
  (d) serie harmonica H(n) = soma de 1/i ~ ln n + 0.5772 (constante de Euler)
  (e) numero de vezes que n pode ser dividido por 2 ate chegar a 1 = floor(log2 n)
*/
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  for (long long n : {10LL, 100LL, 1000LL}) {
    long long s1 = 0, s2 = 0;
    double h = 0;
    for (long long i = 1; i <= n; i++) { s1 += i; s2 += i * i; h += 1.0 / i; }
    cout << "n = " << n << endl;
    cout << "  soma i   = " << s1 << " | formula " << n * (n + 1) / 2 << endl;
    cout << "  soma i^2 = " << s2 << " | formula " << n * (n + 1) * (2 * n + 1) / 6 << endl;
    cout << "  H(n)     = " << h << " | ln n + 0.5772 = " << log((double)n) + 0.5772 << endl;
    int divisoes = 0;
    for (long long x = n; x > 1; x /= 2) divisoes++;
    cout << "  divisoes por 2 = " << divisoes << " | floor(log2 n) = " << (int)floor(log2((double)n)) << endl;
  }
  for (int k : {5, 10, 20}) {
    long long s = 0;
    for (int i = 0; i <= k; i++) s += 1LL << i;
    cout << "soma 2^i, i = 0.." << k << " = " << s << " | 2^(k+1) - 1 = " << (1LL << (k + 1)) - 1 << endl;
  }
  return 0;
}
