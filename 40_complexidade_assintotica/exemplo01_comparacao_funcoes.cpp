/*
Exemplo 1. Comparacao assintotica: o que importa e como o custo cresce quando n fica grande.
Ordem tipica de crescimento: 1 < log n < n < n log n < n^2 < n^3 < 2^n < n!
A tabela mostra o valor de cada funcao e quanto tempo levaria com 10^9 operacoes por segundo.
Algoritmos exponenciais ficam inviaveis ja para n pequeno, por mais rapida que seja a maquina.
*/
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

// escreve um tempo em segundos na unidade mais legivel
void tempo(double ops)
{
  double s = ops / 1e9;
  if (s < 1e-3) printf("%10.2f us", s * 1e6);
  else if (s < 1) printf("%10.2f ms", s * 1e3);
  else if (s < 3600) printf("%10.2f s ", s);
  else if (s < 86400 * 365.0) printf("%10.2f h ", s / 3600);
  else printf("%10.1e an", s / (86400 * 365.0));
}

int main()
{
  const char *nomes[] = {"log n", "n", "n log n", "n^2", "n^3", "2^n", "n!"};
  int ns[] = {10, 20, 50, 100, 1000};
  printf("%-8s", "f(n)");
  for (int n : ns) printf("   n = %-9d", n);
  printf("\n");
  for (int f = 0; f < 7; f++) {
    printf("%-8s", nomes[f]);
    for (int n : ns) {
      double x;
      switch (f) {
        case 0: x = log2(n); break;
        case 1: x = n; break;
        case 2: x = n * log2(n); break;
        case 3: x = pow(n, 2); break;
        case 4: x = pow(n, 3); break;
        case 5: x = pow(2, n); break;
        default: x = tgamma(n + 1.0);   // n! = Gamma(n + 1); vira infinito para n grande
      }
      printf(" ");
      if (isinf(x)) printf("%10s   ", "inf");
      else tempo(x);
      printf("  ");
    }
    printf("\n");
  }
  printf("(us = microssegundos, an = anos; 10^9 operacoes por segundo)\n");
  return 0;
}
