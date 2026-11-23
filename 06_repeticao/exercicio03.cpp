/*
Exercício 3. Ler a idade de 10 pessoas e contar quantas têm menos de 18 anos.
*/
#include <iostream>
using namespace std;

int main()
{
  int idade, menores = 0;
  for (int i = 1; i <= 10; i++) {
    cout << "Idade da pessoa " << i << ": "; cin >> idade;
    if (idade < 18) menores++;   // conta os menores de idade
  }
  cout << menores << " pessoa(s) com menos de 18 anos" << endl;
  return 0;
}
