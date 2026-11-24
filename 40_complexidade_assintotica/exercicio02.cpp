/*
Exercicio 2. Determinar empiricamente a ordem de crescimento de trechos de codigo: contar as execucoes da
instrucao mais interna para n e 2n e calcular log2(custo(2n) / custo(n)), que se aproxima do expoente k
quando o custo e Theta(n^k). Para custos logaritmicos o expoente tende a 0 e para n log n fica pouco acima de 1.
*/
#include <iostream>
#include <cmath>
using namespace std;

long long trecho(int qual, long long n)
{
  long long c = 0;
  switch (qual) {
    case 0: for (long long i = 1; i < n; i *= 2) c++; break;                                    // log n
    case 1: for (long long i = 0; i < n; i++) for (long long j = 1; j < n; j *= 2) c++; break;  // n log n
    case 2: for (long long i = 0; i < n; i++) for (long long j = 0; j < i; j++) c++; break;     // n^2 / 2
    case 3:                                                                                     // n^3 / 6
      for (long long i = 0; i < n; i++)
        for (long long j = 0; j < i; j++)
          for (long long k = 0; k < j; k++) c++;
      break;
    case 4: for (long long i = 0; i * i < n; i++) c++; break;                                   // sqrt n
  }
  return c;
}

int main()
{
  const char *desc[] = {"i *= 2 ate n         ", "n vezes (j *= 2)     ", "j < i                ",
                        "k < j < i            ", "i * i < n            "};
  long long n = 400;
  for (int q = 0; q < 5; q++) {
    long long a = trecho(q, n), b = trecho(q, 2 * n);
    cout << desc[q] << ": custo(n) = " << a << ", custo(2n) = " << b
         << ", expoente estimado = " << log2((double)b / a) << endl;
  }
  return 0;
}
