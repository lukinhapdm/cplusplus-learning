/*
Exercicio 2. Bubble Sort otimizado: parar quando uma passada inteira nao fizer nenhuma troca.
*/
#include <iostream>
using namespace std;

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }
void troca(int &a, int &b) { int t = a; a = b; b = t; }

void bubbleOtimizado(int v[], int n)
{
  bool trocou = true;
  for (int i = 0; i < n - 1 && trocou; i++) {   // para se nao houve troca
    trocou = false;
    for (int j = 0; j < n - 1 - i; j++)
      if (v[j] > v[j + 1]) { troca(v[j], v[j + 1]); trocou = true; }
    cout << "Passada " << i + 1 << ": "; imprime(v, n);
  }
}

int main()
{
  int v[] = {1, 2, 4, 3, 5, 6};   // quase ordenado: termina cedo
  bubbleOtimizado(v, 6);
  return 0;
}
