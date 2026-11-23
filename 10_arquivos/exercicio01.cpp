/*
Exercício 1. Reescrever os programas de 10.1 com uma função para cada operação de arquivo.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// uma funcao para gravar e outra para ler
void grava(string arq)
{
  ofstream out(arq);
  out << "Primeira linha" << endl << "Segunda linha" << endl;
  out.close();
}

void le(string arq)
{
  ifstream in(arq);
  if (!in) { cout << "Erro ao abrir" << endl; return; }
  string linha;
  while (getline(in, linha)) cout << linha << endl;   // le ate o fim
  in.close();
}

int main()
{
  grava("texto.txt");
  le("texto.txt");
  return 0;
}
