/*
Exercicio 1. Comparar as leis de Amdahl e de Gustafson para fracoes sequenciais f = 1%, 5%, 10% e 25%.
- Amdahl (problema de tamanho fixo):      S(p) = 1 / (f + (1 - f) / p)
- Gustafson (problema cresce com p, tempo fixo): S(p) = p - f (p - 1)
Mostrar o speedup para p = 2, 8, 64 e 1024 e o limite de Amdahl 1 / f.
Conclusao: com tamanho fixo a parte sequencial domina; aumentando o problema, o paralelismo volta a compensar.
*/
#include <iostream>
#include <cstdio>
using namespace std;

double amdahl(double f, int p) { return 1.0 / (f + (1 - f) / p); }
double gustafson(double f, int p) { return p - f * (p - 1); }

int main()
{
  int ps[] = {2, 8, 64, 1024};
  for (double f : {0.01, 0.05, 0.10, 0.25}) {
    printf("f = %4.0f%%  (limite de Amdahl: %.0f)\n", f * 100, 1 / f);
    printf("      p     Amdahl   Gustafson\n");
    for (int p : ps) printf("  %5d  %9.2f  %10.2f\n", p, amdahl(f, p), gustafson(f, p));
  }
  return 0;
}
