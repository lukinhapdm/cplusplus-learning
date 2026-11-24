/*
Exemplo 2. Teorema Mestre para T(n) = a T(n/b) + f(n), com a >= 1, b > 1 e f(n) = Theta(n^k):
compara f(n) com n^(log_b a) (o custo das folhas da arvore de recursao):
  Caso 1: k < log_b a  -> T(n) = Theta(n^(log_b a))        (as folhas dominam)
  Caso 2: k = log_b a  -> T(n) = Theta(n^k log n)          (todos os niveis custam igual)
  Caso 3: k > log_b a  -> T(n) = Theta(n^k)                (a raiz domina; vale a condicao de regularidade
                                                           a f(n/b) <= c f(n), automatica para polinomios)
O programa classifica cada recorrencia e confere a razao T(n) / resposta para n grande (deve estabilizar).
*/
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

struct Recorrencia { const char *nome; int a, b; double k; };

// calcula T(n) numericamente com T(1) = 1 (n potencia de b)
double calcula(const Recorrencia &r, double n)
{
  if (n <= 1) return 1;
  return r.a * calcula(r, n / r.b) + pow(n, r.k);
}

int main()
{
  Recorrencia rs[] = {
    {"8T(n/2) + n^2  (mult. de matrizes ingenua D&C)", 8, 2, 2},
    {"7T(n/2) + n^2  (Strassen)", 7, 2, 2},
    {"2T(n/2) + n    (mergesort)", 2, 2, 1},
    {"T(n/2) + 1     (pesquisa binaria)", 1, 2, 0},
    {"3T(n/4) + n^2", 3, 4, 2},
    {"4T(n/2) + n^3", 4, 2, 3},
  };
  for (const Recorrencia &r : rs) {
    double e = log((double)r.a) / log((double)r.b);   // log_b a
    char resposta[60];
    double (*g)(double, double, double);
    if (fabs(r.k - e) < 1e-9) {
      snprintf(resposta, sizeof(resposta), "caso 2: Theta(n^%.2f log n)", e);
      g = [](double n, double e, double) { return pow(n, e) * log2(n); };
    } else if (r.k < e) {
      snprintf(resposta, sizeof(resposta), "caso 1: Theta(n^%.2f)", e);
      g = [](double n, double e, double) { return pow(n, e); };
    } else {
      snprintf(resposta, sizeof(resposta), "caso 3: Theta(n^%.2f)", r.k);
      g = [](double n, double, double k) { return pow(n, k); };
    }
    printf("T(n) = %-48s log_b a = %.2f -> %s\n", r.nome, e, resposta);
    printf("    T(n)/resposta: ");
    for (int p = 4; p <= 16; p += 4) {   // n = b^p
      double n = pow(r.b, p);
      printf("%.3f  ", calcula(r, n) / g(n, e, r.k));
    }
    printf("\n");
  }
  return 0;
}
