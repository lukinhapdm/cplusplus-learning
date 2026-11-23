/*
Exercicio 2. Funcao area sobrecarregada: quadrado (lado), retangulo (base, altura) e circulo (raio double + marcador char).
*/
#include <iostream>
using namespace std;

double area(double lado) { return lado * lado; }                // quadrado
double area(double b, double h) { return b * h; }               // retangulo
double area(double r, char) { return 3.14159 * r * r; }         // circulo: o char so diferencia a assinatura

int main()
{
  cout << "Quadrado 3: " << area(3.0) << endl;
  cout << "Retangulo 3x4: " << area(3.0, 4.0) << endl;
  cout << "Circulo r=2: " << area(2.0, 'c') << endl;
  return 0;
}
