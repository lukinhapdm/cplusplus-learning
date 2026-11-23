/*
Exercicio 1. Funcao que recebe um vetor (por ponteiro) e seu tamanho e devolve, por ponteiros, o maior e o menor valor.
*/
#include <iostream>
using namespace std;

void maiorMenor(int *v, int n, int *maior, int *menor)
{
  *maior = *menor = v[0];
  for (int i = 1; i < n; i++) {
    if (v[i] > *maior) *maior = v[i];
    if (v[i] < *menor) *menor = v[i];
  }
}

int main()
{
  int v[6] = {4, -2, 9, 7, 0, 3}, ma, me;
  maiorMenor(v, 6, &ma, &me);   // passa os enderecos para receber o resultado
  cout << "Maior: " << ma << " | Menor: " << me << endl;
  return 0;
}
