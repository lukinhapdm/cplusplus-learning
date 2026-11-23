/*
7.2.5 Exercício 2. Matriz 10x3 de notas: para cada aluno maior nota e média.
*/
#include <iostream>
using namespace std;

int main()
{
  float notas[10][3];
  // cada linha = um aluno, cada coluna = uma prova
  for (int i = 0; i < 10; i++) {
    cout << "3 notas do aluno " << i + 1 << ": ";
    for (int j = 0; j < 3; j++) cin >> notas[i][j];
  }
  for (int i = 0; i < 10; i++) {
    float maior = notas[i][0], soma = 0;
    for (int j = 0; j < 3; j++) {
      if (notas[i][j] > maior) maior = notas[i][j];
      soma += notas[i][j];
    }
    cout << "Aluno " << i + 1 << " - maior: " << maior << " | media: " << soma / 3 << endl;
  }
  return 0;
}
