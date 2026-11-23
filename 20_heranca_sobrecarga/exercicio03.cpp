/*
Exercicio 3. Classe Vetor2D com operadores sobrecarregados: +, -, * (por escalar), == e <<.
*/
#include <iostream>
using namespace std;

class Vetor2D {
  double x, y;
public:
  Vetor2D(double x = 0, double y = 0) : x(x), y(y) {}
  Vetor2D operator+(const Vetor2D &o) const { return Vetor2D(x + o.x, y + o.y); }
  Vetor2D operator-(const Vetor2D &o) const { return Vetor2D(x - o.x, y - o.y); }
  Vetor2D operator*(double k) const { return Vetor2D(x * k, y * k); }
  bool operator==(const Vetor2D &o) const { return x == o.x && y == o.y; }
  friend ostream &operator<<(ostream &out, const Vetor2D &v) { return out << "(" << v.x << ", " << v.y << ")"; }
};

int main()
{
  Vetor2D a(1, 2), b(3, 4);
  cout << a + b << " " << b - a << " " << a * 3 << endl;
  cout << (a * 2 == Vetor2D(2, 4) ? "iguais" : "diferentes") << endl;
  return 0;
}
