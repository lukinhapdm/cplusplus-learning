/*
Exercício 4. Calcular e mostrar o IMC (peso / altura^2).
*/
#include <iostream>
using namespace std;

int main()
{
  float peso, altura, imc;
  cout << "Peso (kg): "; cin >> peso;
  cout << "Altura (m): "; cin >> altura;
  imc = peso / (altura * altura);   // formula do IMC
  cout << "IMC: " << imc << endl;
  return 0;
}
