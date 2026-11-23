/*
7.1.4 Exercício 10. 100 aleatórios em [0,99] (rand()%100); imprimir os > 50 e suas posições.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
  int v[100];
  srand(time(0));   // muda a semente para gerar numeros diferentes a cada execucao
  for (int i = 0; i < 100; i++) v[i] = rand() % 100;   // resto da divisao: 0 a 99
  for (int i = 0; i < 100; i++)
    if (v[i] > 50) cout << "Posicao " << i << ": " << v[i] << endl;
  return 0;
}
