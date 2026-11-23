/*
Exemplo 3. Heap Sort e busca binaria (que exige o vetor ordenado).
*/
#include <iostream>
using namespace std;

void troca(int &a, int &b) { int t = a; a = b; b = t; }

// faz o no i "descer" ate o pai ser maior que os filhos (max-heap)
void desce(int v[], int n, int i)
{
  int maior = i, e = 2 * i + 1, d = 2 * i + 2;
  if (e < n && v[e] > v[maior]) maior = e;
  if (d < n && v[d] > v[maior]) maior = d;
  if (maior != i) { troca(v[i], v[maior]); desce(v, n, maior); }
}

void heapSort(int v[], int n)
{
  for (int i = n / 2 - 1; i >= 0; i--) desce(v, n, i);   // monta o heap
  for (int fim = n - 1; fim > 0; fim--) {
    troca(v[0], v[fim]);   // o maior (raiz) vai para o final
    desce(v, fim, 0);      // arruma o heap no que sobrou
  }
}

// a cada passo descarta metade do vetor: O(log n)
int buscaBinaria(int v[], int n, int x)
{
  int ini = 0, fim = n - 1;
  while (ini <= fim) {
    int meio = (ini + fim) / 2;
    if (v[meio] == x) return meio;
    if (v[meio] < x) ini = meio + 1;   // esta na metade direita
    else fim = meio - 1;               // esta na metade esquerda
  }
  return -1;
}

int main()
{
  int v[] = {12, 3, 17, 8, 34, 25, 1};
  heapSort(v, 7);
  for (int x : v) cout << x << " ";
  cout << endl;
  cout << "25 esta na posicao " << buscaBinaria(v, 7, 25) << endl;
  cout << "99 -> " << buscaBinaria(v, 7, 99) << " (nao encontrado)" << endl;
  return 0;
}
