/*
Exercício 2. Ler string; função conta 'a', troca por 'b' e retorna a qtd; main mostra qtd e string.
*/
#include <iostream>
using namespace std;

// conta os 'a', troca por 'b' e devolve a quantidade
int trocaA(char s[])
{
  int c = 0;
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == 'a') { s[i] = 'b'; c++; }
  return c;
}

int main()
{
  char s[100];
  cout << "Texto: "; cin.getline(s, 100);
  int qtd = trocaA(s);
  cout << "Quantidade de 'a': " << qtd << "\nTexto alterado: " << s << endl;
  return 0;
}
