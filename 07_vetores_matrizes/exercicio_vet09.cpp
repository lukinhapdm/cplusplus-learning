/*
7.1.4 Exercício 9. Função que ordena o vetor em ordem crescente; testar no main.
*/
#include <iostream>
using namespace std;

// bubble sort: compara vizinhos e troca se estiverem fora de ordem
void ordena(int v[], int n)
{
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
      if (v[j] > v[j + 1]) { int aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux; }
}

int main()
{
  int v[6] = {5, 2, 9, 1, 7, 3};
  ordena(v, 6);   // vetor e passado por referencia automaticamente
  for (int i = 0; i < 6; i++) cout << v[i] << " ";
  cout << endl;
  return 0;
}
