/*
Exemplo 1. Ordenacoes simples O(n^2): Bubble, Selection e Insertion Sort.
*/
#include <iostream>
using namespace std;

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }
void troca(int &a, int &b) { int t = a; a = b; b = t; }

// Bubble: o maior "sobe" para o fim a cada passada
void bubble(int v[], int n)
{
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
      if (v[j] > v[j + 1]) troca(v[j], v[j + 1]);
}

// Selection: escolhe o menor e coloca na posicao i
void selection(int v[], int n)
{
  for (int i = 0; i < n - 1; i++) {
    int m = i;
    for (int j = i + 1; j < n; j++) if (v[j] < v[m]) m = j;
    troca(v[i], v[m]);
  }
}

// Insertion: insere cada elemento na parte ja ordenada (como cartas na mao)
void insertion(int v[], int n)
{
  for (int i = 1; i < n; i++) {
    int x = v[i], j = i - 1;
    while (j >= 0 && v[j] > x) { v[j + 1] = v[j]; j--; }
    v[j + 1] = x;
  }
}

int main()
{
  int a[] = {5, 2, 9, 1, 7}, b[] = {5, 2, 9, 1, 7}, c[] = {5, 2, 9, 1, 7};
  bubble(a, 5); imprime(a, 5);
  selection(b, 5); imprime(b, 5);
  insertion(c, 5); imprime(c, 5);
  return 0;
}
