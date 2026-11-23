/*
Exercicio 1. Transformar o TAD Retangulo (struct + funcoes) em uma classe com atributos privados e metodos area e perimetro.
*/
#include <iostream>
using namespace std;

class Retangulo {
private:
  float base, altura;
public:
  // set valida antes de guardar
  void setMedidas(float b, float h) { base = b > 0 ? b : 1; altura = h > 0 ? h : 1; }
  float area() { return base * altura; }
  float perimetro() { return 2 * (base + altura); }
};

int main()
{
  Retangulo r;
  float b, h;
  cout << "Base e altura: "; cin >> b >> h;
  r.setMedidas(b, h);
  cout << "Area: " << r.area() << " | Perimetro: " << r.perimetro() << endl;
  return 0;
}
