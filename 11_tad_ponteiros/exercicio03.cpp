/*
Exercicio 3. TAD Retangulo com funcoes: cria, area, perimetro e libera.
*/
#include <iostream>
using namespace std;

struct Retangulo { float base, altura; };

Retangulo *cria(float b, float h)
{
  Retangulo *r = new Retangulo;
  r->base = b; r->altura = h;
  return r;
}

float area(Retangulo *r) { return r->base * r->altura; }
float perimetro(Retangulo *r) { return 2 * (r->base + r->altura); }
void libera(Retangulo *r) { delete r; }

int main()
{
  float b, h;
  cout << "Base e altura: "; cin >> b >> h;
  Retangulo *r = cria(b, h);
  cout << "Area: " << area(r) << " | Perimetro: " << perimetro(r) << endl;
  libera(r);
  return 0;
}
