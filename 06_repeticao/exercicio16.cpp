/*
Exercício 16. Função que lê valores positivos (qtd indeterminada) e retorna a média.
*/
#include <iostream>
using namespace std;

// le valores ate digitar um nao positivo e retorna a media
float mediaPositivos()
{
  float v, soma = 0;
  int qtd = 0;
  cout << "Valores positivos (0 ou negativo encerra): ";
  cin >> v;
  while (v > 0) { soma += v; qtd++; cin >> v; }
  if (qtd == 0) return 0;
  return soma / qtd;
}

int main()
{
  cout << "Media: " << mediaPositivos() << endl;
  return 0;
}
