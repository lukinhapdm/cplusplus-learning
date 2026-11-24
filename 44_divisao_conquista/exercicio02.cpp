/*
Exercicio 2. Selecao do k-esimo menor elemento (ex.: mediana) sem ordenar tudo.
Quickselect: particiona como no quicksort e continua so no lado que contem a posicao k.
Caso medio O(n) (T(n) = T(n/2) + n), pior caso O(n^2). Com pivo aleatorio o pior caso fica improvavel.
Comparar o numero de comparacoes com o de ordenar o vetor (~n log2 n).
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

long long comp;

// devolve o k-esimo menor (k comeca em 0) de v[ini..fim]
int quickselect(vector<int> &v, int ini, int fim, int k)
{
  while (true) {
    if (ini == fim) return v[ini];
    swap(v[ini + rand() % (fim - ini + 1)], v[fim]);   // pivo aleatorio vai para o fim
    int pivo = v[fim], i = ini;
    for (int j = ini; j < fim; j++) { comp++; if (v[j] < pivo) swap(v[i++], v[j]); }
    swap(v[i], v[fim]);                                // pivo na posicao final i
    if (k == i) return v[i];
    if (k < i) fim = i - 1;   // descarta a direita
    else ini = i + 1;         // descarta a esquerda
  }
}

int main()
{
  srand(12);
  for (int n : {1001, 100001}) {
    vector<int> v(n);
    for (int &x : v) x = rand() % 1000000;
    vector<int> ordenado = v;
    sort(ordenado.begin(), ordenado.end());
    comp = 0;
    int med = quickselect(v, 0, n - 1, n / 2);
    cout << "n = " << n << ": mediana " << med << (med == ordenado[n / 2] ? " (confere)" : " (ERRO)")
         << ", " << comp << " comparacoes (" << (double)comp / n << " n); ordenar: ~" << (long long)(n * log2(n)) << endl;
  }
  return 0;
}
