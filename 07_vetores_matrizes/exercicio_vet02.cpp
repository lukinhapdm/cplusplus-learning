/*
7.1.4 Exercicio 2 - resposta

(a) Para cada posicao, o programa guarda o maior entre v1[i] e v2[i]:
    v3 = { 12, 3, 14, 3, 19, 11, 51, 4, 20, 21 }

(b) O programa le dois vetores de 10 inteiros e cria um terceiro vetor
    onde cada posicao recebe o maior valor entre as posicoes correspondentes
    dos dois vetores. Depois imprime esse terceiro vetor.
*/
#include <iostream>
using namespace std;

int main()
{
  int v1[10] = {7, 3, 12, -6, 19, 11, 6, 4, 0, 21};
  int v2[10] = {12, -16, 14, 3, 8, 11, 51, -1, 20, 2};
  int v3[10];
  for (int i = 0; i < 10; ++i)
    v3[i] = (v1[i] > v2[i]) ? v1[i] : v2[i];   // fica com o maior
  for (int i = 0; i < 10; ++i) cout << v3[i] << " ";
  cout << endl;
  return 0;
}
