/*
Exemplo 2. Notacoes assintoticas (para n >= n0 e constantes c > 0):
  f = O(g)  se f(n) <= c g(n)            (g e limite superior)
  f = Omega(g) se f(n) >= c g(n)         (g e limite inferior)
  f = Theta(g) se c1 g(n) <= f(n) <= c2 g(n)   (mesma ordem: O e Omega ao mesmo tempo)
  f = o(g)  se f(n)/g(n) -> 0            (g cresce estritamente mais rapido)
  f = omega(g) se f(n)/g(n) -> infinito  (f cresce estritamente mais rapido)
Pelo limite L = lim f(n)/g(n): L = 0 -> o(g); 0 < L < inf -> Theta(g); L = inf -> omega(g).
Aqui o programa calcula a razao para n crescente e mostra a tendencia (nao e prova, e intuicao!).
Exemplo da definicao: f(n) = 3n^2 + 10n + 5 e O(n^2) com c = 4 e n0 = 11, pois 10n + 5 <= n^2 para n >= 11.
*/
#include <iostream>
#include <cmath>
using namespace std;

double f1(double n) { return 3 * n * n + 10 * n + 5; }
double g1(double n) { return n * n; }

void razao(const char *nome, double (*f)(double), double (*g)(double))
{
  cout << nome << ": ";
  for (double n = 10; n <= 1e7; n *= 100) cout << f(n) / g(n) << "  ";
  cout << endl;
}

double nlogn(double n) { return n * log2(n); }
double n2(double n) { return n * n; }
double n15(double n) { return pow(n, 1.5); }
double logn(double n) { return log2(n); }
double raiz(double n) { return sqrt(n); }

int main()
{
  // procura o menor n0 tal que f1(n) <= 4 g1(n) para todo n >= n0 (testando ate 10^6)
  int n0 = 1;
  for (int n = 1; n <= 1000000; n++) if (f1(n) > 4 * g1(n)) n0 = n + 1;
  cout << "3n^2 + 10n + 5 <= 4n^2 para todo n >= " << n0 << "  => O(n^2)" << endl;

  cout << "\nRazao f/g para n = 10, 1000, 10^5, 10^7:" << endl;
  razao("(3n^2+10n+5) / n^2  -> 3, Theta ", f1, g1);
  razao("n log n / n^2       -> 0, o     ", nlogn, n2);
  razao("n^2 / n^1.5         -> inf, omega", n2, n15);
  razao("log n / sqrt(n)     -> 0, o     ", logn, raiz);
  return 0;
}
