/*
Exercicio 3. Classe Termometro que guarda a temperatura em Celsius e converte para Fahrenheit e Kelvin. Nao aceitar valor abaixo de -273.15.
*/
#include <iostream>
using namespace std;

class Termometro {
private:
  double celsius = 0;
public:
  bool setCelsius(double c)
  {
    if (c < -273.15) return false;   // abaixo do zero absoluto
    celsius = c;
    return true;
  }
  double fahrenheit() { return celsius * 9 / 5 + 32; }
  double kelvin() { return celsius + 273.15; }
};

int main()
{
  Termometro t; double c;
  cout << "Temperatura em C: "; cin >> c;
  if (!t.setCelsius(c)) { cout << "Valor invalido" << endl; return 0; }
  cout << "F: " << t.fahrenheit() << " | K: " << t.kelvin() << endl;
  return 0;
}
