/*
Exercicio 2. Ler N, alocar dinamicamente um vetor de N inteiros, ler os valores e mostrar a media. Liberar a memoria no final.
*/
#include <iostream>
using namespace std;

int main()
{
  int n;
  cout << "N: "; cin >> n;
  int *v = new int[n];   // tamanho definido em tempo de execucao
  float soma = 0;
  for (int i = 0; i < n; i++) { cin >> v[i]; soma += v[i]; }
  cout << "Media: " << soma / n << endl;
  delete[] v;
  return 0;
}
