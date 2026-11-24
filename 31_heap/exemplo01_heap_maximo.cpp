/*
Exemplo 1. Heap maximo: arvore binaria quase completa guardada em vetor, em que cada pai e >= seus filhos.
Com indices a partir de 0: filhos de i em 2i+1 e 2i+2, pai de i em (i-1)/2. O maior fica sempre em v[0].
- insere: coloca no final e "sobe" trocando com o pai enquanto for maior. O(log n)
- removeMax: tira v[0], coloca o ultimo no lugar e "desce" trocando com o maior filho. O(log n)
- constroi: transforma um vetor qualquer em heap descendo os nos de n/2-1 ate 0. O(n)
*/
#include <iostream>
using namespace std;

class HeapMax {
  int *v, n, cap;

  void troca(int i, int j) { int a = v[i]; v[i] = v[j]; v[j] = a; }

  void sobe(int i)
  {
    while (i > 0 && v[(i - 1) / 2] < v[i]) {
      troca(i, (i - 1) / 2);
      i = (i - 1) / 2;
    }
  }

  void desce(int i)
  {
    while (2 * i + 1 < n) {
      int f = 2 * i + 1;                     // filho esquerdo
      if (f + 1 < n && v[f + 1] > v[f]) f++; // escolhe o maior filho
      if (v[i] >= v[f]) break;               // ja esta no lugar
      troca(i, f);
      i = f;
    }
  }

public:
  HeapMax(int c) : v(new int[c]), n(0), cap(c) {}
  ~HeapMax() { delete[] v; }
  bool vazio() const { return n == 0; }
  int maximo() const { return v[0]; }

  bool insere(int x)
  {
    if (n == cap) return false;
    v[n] = x;
    sobe(n++);
    return true;
  }

  int removeMax()
  {
    int m = v[0];
    v[0] = v[--n];
    desce(0);
    return m;
  }

  void constroi(const int a[], int tam)
  {
    n = tam;
    for (int i = 0; i < n; i++) v[i] = a[i];
    for (int i = n / 2 - 1; i >= 0; i--) desce(i);   // folhas ja sao heaps
  }

  void imprime() const { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }
};

int main()
{
  HeapMax h(20);
  for (int x : {15, 40, 8, 23, 50, 4, 31}) { h.insere(x); cout << "insere " << x << ": "; h.imprime(); }
  cout << "Removendo em ordem: ";
  while (!h.vazio()) cout << h.removeMax() << " ";
  cout << endl;

  int a[] = {3, 9, 2, 1, 4, 5, 8, 7};
  h.constroi(a, 8);
  cout << "Heap construido em O(n): "; h.imprime();
  return 0;
}
