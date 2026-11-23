/*
Exercicio 3. Funcao que recebe um vetor de Forma* e devolve a soma das areas, funcionando para qualquer forma nova (Quadrado, Triangulo).
*/
#include <iostream>
using namespace std;

class Forma {
public:
  virtual double area() const = 0;
  virtual ~Forma() {}
};
class Quadrado : public Forma { double l; public:
  Quadrado(double l) : l(l) {}
  double area() const override { return l * l; } };
class Triangulo : public Forma { double b, h; public:
  Triangulo(double b, double h) : b(b), h(h) {}
  double area() const override { return b * h / 2; } };

// nao precisa saber qual forma e: so chama area()
double areaTotal(Forma *v[], int n)
{
  double s = 0;
  for (int i = 0; i < n; i++) s += v[i]->area();
  return s;
}

int main()
{
  Forma *v[3] = {new Quadrado(2), new Triangulo(4, 3), new Quadrado(1)};
  cout << "Area total: " << areaTotal(v, 3) << endl;   // 4 + 6 + 1 = 11
  for (Forma *f : v) delete f;
  return 0;
}
