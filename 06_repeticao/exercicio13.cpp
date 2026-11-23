/*
Exercício 13. Menu: 1-média aritmética (2 notas), 2-média ponderada (3 notas e pesos), 3-sair; tratar opção inválida.
*/
#include <iostream>
using namespace std;

int main()
{
  int op;
  do {
    cout << "\nMenu de opcoes:\n1. Media aritmetica\n2. Media ponderada\n3. Sair\nOpcao: ";
    cin >> op;
    if (op == 1) {
      float a, b;
      cout << "Duas notas: "; cin >> a >> b;
      cout << "Media: " << (a + b) / 2 << endl;
    } else if (op == 2) {
      float n1, n2, n3, p1, p2, p3;
      cout << "Tres notas: "; cin >> n1 >> n2 >> n3;
      cout << "Tres pesos: "; cin >> p1 >> p2 >> p3;
      cout << "Media: " << (n1*p1 + n2*p2 + n3*p3) / (p1 + p2 + p3) << endl;
    } else if (op != 3)
      cout << "Opcao invalida!" << endl;
  } while (op != 3);   // repete o menu ate escolher sair
  return 0;
}
