/*
Exercicio 2. Encontrar os k maiores elementos de uma sequencia grande usando um heap MINIMO de tamanho k:
o topo e o menor dos k melhores; cada elemento novo maior que o topo substitui o topo. Custo O(n log k).
*/
#include <iostream>
#include <utility>
#include <cstdlib>
using namespace std;

void desceMin(int h[], int n, int i)
{
  while (2 * i + 1 < n) {
    int f = 2 * i + 1;
    if (f + 1 < n && h[f + 1] < h[f]) f++;   // menor filho
    if (h[i] <= h[f]) break;
    swap(h[i], h[f]); i = f;
  }
}

void sobeMin(int h[], int i) { while (i > 0 && h[(i - 1) / 2] > h[i]) { swap(h[i], h[(i - 1) / 2]); i = (i - 1) / 2; } }

int main()
{
  const int K = 5, N = 1000;
  int h[K], n = 0;
  srand(11);
  int maiorVisto = 0;
  for (int i = 0; i < N; i++) {
    int x = rand() % 10000;
    if (x > maiorVisto) maiorVisto = x;
    if (n < K) { h[n] = x; sobeMin(h, n++); }       // ainda nao encheu
    else if (x > h[0]) { h[0] = x; desceMin(h, K, 0); }   // melhor que o pior dos k
  }
  // tira do heap minimo: sai do menor para o maior
  int saida[K];
  for (int i = K - 1; i >= 0; i--) { saida[i] = h[0]; h[0] = h[--n]; desceMin(h, n, 0); }
  cout << "Os " << K << " maiores (do maior para o menor): ";
  for (int i = 0; i < K; i++) cout << saida[i] << " ";
  cout << "\nMaior visto: " << maiorVisto << endl;
  return 0;
}
