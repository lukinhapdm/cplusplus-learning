/*
Exemplo 2. Recursividade: uma funcao que chama a si mesma resolvendo instancias menores do problema.
Precisa de (1) caso base, que para a recursao, e (2) passo recursivo, que se aproxima do caso base.
O custo e descrito por uma equacao de recorrencia. Ex.:
  - fatorial:  T(n) = T(n-1) + 1          -> n chamadas
  - Fibonacci ingenuo: T(n) = T(n-1) + T(n-2) + 1 -> cresce como 1.618^n (exponencial!)
  - Hanoi:     T(n) = 2T(n-1) + 1         -> 2^n - 1 movimentos
Recursao nem sempre e ineficiente: o problema do Fibonacci ingenuo e recalcular os mesmos valores.
*/
#include <iostream>
using namespace std;

long long chamadas;

long long fatorial(int n)
{
  chamadas++;
  if (n <= 1) return 1;          // caso base
  return n * fatorial(n - 1);    // passo recursivo
}

long long fibRec(int n)
{
  chamadas++;
  if (n < 2) return n;
  return fibRec(n - 1) + fibRec(n - 2);   // recalcula os mesmos subproblemas muitas vezes
}

long long fibIter(int n)
{
  long long a = 0, b = 1;
  for (int i = 0; i < n; i++) { long long c = a + b; a = b; b = c; }
  return a;
}

long long movimentos;
void hanoi(int n, char origem, char destino, char aux, bool mostra)
{
  if (n == 0) return;
  hanoi(n - 1, origem, aux, destino, mostra);   // tira os n-1 de cima
  movimentos++;
  if (mostra) cout << "  disco " << n << ": " << origem << " -> " << destino << endl;
  hanoi(n - 1, aux, destino, origem, mostra);   // coloca os n-1 por cima
}

int main()
{
  chamadas = 0;
  cout << "10! = " << fatorial(10) << " (" << chamadas << " chamadas)" << endl;

  for (int n : {10, 20, 30}) {
    chamadas = 0;
    long long f = fibRec(n);
    cout << "fib(" << n << ") = " << f << ": recursivo com " << chamadas << " chamadas, iterativo com " << n << " passos ("
         << fibIter(n) << ")" << endl;
  }

  cout << "Hanoi com 3 discos:" << endl;
  movimentos = 0;
  hanoi(3, 'A', 'C', 'B', true);
  for (int n : {10, 20}) {
    movimentos = 0;
    hanoi(n, 'A', 'C', 'B', false);
    cout << "Hanoi com " << n << " discos: " << movimentos << " movimentos (2^n - 1 = " << (1LL << n) - 1 << ")" << endl;
  }
  return 0;
}
