/*
Exemplo 1. Resolucao de recorrencias pelo metodo da expansao (iteracao): substitui T do lado direito
repetidamente ate chegar ao caso base, soma os termos e obtem uma formula fechada.
  (a) T(n) = T(n-1) + n,   T(1) = 1  -> T(n) = n + (n-1) + ... + 1 = n(n+1)/2       (ex.: selecao)
  (b) T(n) = 2T(n/2) + n,  T(1) = 1  -> log2 n niveis, cada um somando n: n log2 n + n  (ex.: mergesort)
  (c) T(n) = T(n/2) + 1,   T(1) = 1  -> log2 n + 1                                    (ex.: pesquisa binaria)
  (d) T(n) = 2T(n-1) + 1,  T(1) = 1  -> 2^n - 1                                       (ex.: Hanoi)
O programa calcula a recorrencia diretamente e compara com a formula fechada (n potencia de 2).
*/
#include <iostream>
#include <cmath>
using namespace std;

long long Ta(long long n) { return n == 1 ? 1 : Ta(n - 1) + n; }
long long Tb(long long n) { return n == 1 ? 1 : 2 * Tb(n / 2) + n; }
long long Tc(long long n) { return n == 1 ? 1 : Tc(n / 2) + 1; }
long long Td(long long n) { return n == 1 ? 1 : 2 * Td(n - 1) + 1; }

// mostra a expansao de (b) passo a passo
void expandeB(long long n)
{
  cout << "Expansao de T(" << n << ") = 2T(n/2) + n:" << endl;
  long long mult = 1, soma = 0, m = n;
  while (m > 1) {
    soma += mult * m;   // termo do nivel: 2^i * (n / 2^i) = n
    cout << "  = " << mult * 2 << "T(" << m / 2 << ") + " << soma << endl;
    mult *= 2; m /= 2;
  }
  cout << "  = " << mult << " * T(1) + " << soma << " = " << mult + soma << endl;
}

int main()
{
  cout << "n\t(a)\tn(n+1)/2\t(b)\tn lg n + n\t(c)\tlg n + 1" << endl;
  for (long long n = 1; n <= 1024; n *= 4) {
    long long lg = (long long)log2((double)n);
    cout << n << "\t" << Ta(n) << "\t" << n * (n + 1) / 2 << "\t\t" << Tb(n) << "\t" << n * lg + n
         << "\t\t" << Tc(n) << "\t" << lg + 1 << endl;
  }
  for (int n : {5, 10, 20}) cout << "(d) T(" << n << ") = " << Td(n) << ", 2^n - 1 = " << (1LL << n) - 1 << endl;
  expandeB(16);
  return 0;
}
