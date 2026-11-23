/*
7.1.4 Exercício 8. Função que retorna por referência o maior e o 2º maior do vetor; testar no main.
*/
#include <iostream>
#include <climits>
using namespace std;

const int MAX = 100;   // tamanho maximo (C++ padrao nao aceita vetor com tamanho lido)

void doisMaiores(int v[], int n, int &m1, int &m2)
{
  m1 = m2 = INT_MIN;   // comeca com o menor int possivel
  for (int i = 0; i < n; i++) {
    if (v[i] > m1) { m2 = m1; m1 = v[i]; }   // novo maior: o antigo vira o 2o
    else if (v[i] > m2) m2 = v[i];           // so supera o 2o
  }
}

int main()
{
  int n, m1, m2;
  cout << "Tamanho: "; cin >> n;
  if (n > MAX) n = MAX;
  int v[MAX];
  cout << "Valores: "; for (int i = 0; i < n; i++) cin >> v[i];
  doisMaiores(v, n, m1, m2);
  cout << "Maior: " << m1 << " | Segundo maior: " << m2 << endl;
  return 0;
}
