/*
Exercicio 1. Pesquisa sequencial em vetor ordenado: parar assim que encontrar um elemento maior
que a chave (a chave nao pode estar mais a frente). Mostrar o numero de comparacoes.
*/
#include <iostream>
using namespace std;

int sequencialOrdenada(int v[], int n, int chave, int &comp)
{
  comp = 0;
  for (int i = 0; i < n; i++) {
    comp++;
    if (v[i] == chave) return i;
    if (v[i] > chave) return -1;   // passou do ponto: nao existe
  }
  return -1;
}

int main()
{
  int v[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
  int n = 10, comp;
  int chaves[] = {23, 13, 1, 100};
  for (int c : chaves) {
    int p = sequencialOrdenada(v, n, c, comp);
    cout << "Chave " << c << ": posicao " << p << " (" << comp << " comparacoes)" << endl;
  }
  return 0;
}
