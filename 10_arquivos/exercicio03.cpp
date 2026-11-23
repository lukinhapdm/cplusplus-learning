/*
Exercício 3. Reescrever o programa de 10.2.2 (contar linhas e caracteres) com funções.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// le o arquivo caractere por caractere, contando linhas e caracteres
void conta(string arq, int &linhas, int &chars)
{
  ifstream in(arq);
  char c;
  linhas = chars = 0;
  while (in.get(c)) {
    chars++;
    if (c == '\n') linhas++;
  }
  in.close();
}

int main()
{
  int l, c;
  conta("caracteres.txt", l, c);
  cout << "Linhas: " << l << " | Caracteres: " << c << endl;
  return 0;
}
