/*
7.2.5 Exercício 1. verificaValor(matriz 4x4, x): true se x está na matriz; main com consultas.
*/
#include <iostream>
using namespace std;

bool verificaValor(int m[4][4], int x)
{
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (m[i][j] == x) return true;
  return false;
}

int main()
{
  int m[4][4], x;
  cout << "Preencha a matriz 4x4: ";
  for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) cin >> m[i][j];
  char resp = 's';
  while (resp == 's') {
    cout << "Valor a procurar: "; cin >> x;
    cout << (verificaValor(m, x) ? "Esta na matriz" : "Nao esta na matriz") << endl;
    cout << "Outro? (s/n) "; cin >> resp;
  }
  return 0;
}
