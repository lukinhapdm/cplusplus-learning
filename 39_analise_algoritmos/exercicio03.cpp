/*
Exercicio 3. Pesquisa binaria recursiva com contagem de chamadas. Para n = 2^k - 1, o pior caso faz
exatamente k chamadas que comparam (T(n) = T(n/2) + 1 = O(log n)). Conferir para varios k.
Tambem verificar que a soma dos digitos de um numero, feita recursivamente, faz tantas chamadas quanto digitos.
*/
#include <iostream>
using namespace std;

int chamadas;

int binaria(int v[], int esq, int dir, int chave)
{
  if (esq > dir) return -1;
  chamadas++;
  int meio = (esq + dir) / 2;
  if (v[meio] == chave) return meio;
  if (chave < v[meio]) return binaria(v, esq, meio - 1, chave);
  return binaria(v, meio + 1, dir, chave);
}

int somaDigitos(long long n)
{
  chamadas++;
  if (n < 10) return n;
  return n % 10 + somaDigitos(n / 10);
}

int main()
{
  for (int k = 1; k <= 16; k += 5) {
    int n = (1 << k) - 1;
    int *v = new int[n];
    for (int i = 0; i < n; i++) v[i] = i;
    int pior = 0;
    for (int c = 0; c < n; c++) {
      chamadas = 0; binaria(v, 0, n - 1, c);
      if (chamadas > pior) pior = chamadas;
    }
    cout << "n = " << n << ": pior caso " << pior << " chamadas (k = " << k << ")" << endl;
    delete[] v;
  }
  chamadas = 0;
  cout << "Soma dos digitos de 9876543210 = " << somaDigitos(9876543210LL) << " (" << chamadas << " chamadas)" << endl;
  return 0;
}
