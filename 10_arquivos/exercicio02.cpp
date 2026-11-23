/*
Exercício 2. Reescrever o programa de 10.2.1 (gravar caracteres até '.') com funções.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// grava caractere por caractere ate o usuario digitar '.'
void gravaCaracteres(string arq)
{
  ofstream out(arq);
  char c;
  cout << "Digite o texto (termine com .): ";
  while (cin.get(c) && c != '.') out.put(c);
  out.close();
}

int main()
{
  gravaCaracteres("caracteres.txt");
  return 0;
}
