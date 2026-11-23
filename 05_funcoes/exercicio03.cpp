/*
Exercício 3. Função que ordena três argumentos char (ex.: 'B','A','C' -> 'A','B','C').
*/
#include <iostream>
using namespace std;

// troca dois chars de lugar
void troca(char &x, char &y) { char aux = x; x = y; y = aux; }

// ordena os 3 chars comparando de dois em dois
void ordena(char &a, char &b, char &c)
{
  if (a > b) troca(a, b);
  if (a > c) troca(a, c);
  if (b > c) troca(b, c);
}

int main()
{
  char ch1 = 'B', ch2 = 'A', ch3 = 'C';
  ordena(ch1, ch2, ch3);
  cout << ch1 << " " << ch2 << " " << ch3 << endl;   // A B C
  return 0;
}
