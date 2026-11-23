/*
Exemplo 2. Sobrecarga de funcoes, de construtores e de operadores (+, == e <<).
*/
#include <iostream>
using namespace std;

// sobrecarga de funcao: mesmo nome, parametros diferentes
int soma(int a, int b) { return a + b; }
double soma(double a, double b) { return a + b; }
int soma(int a, int b, int c) { return a + b + c; }

class Fracao {
private:
  int num, den;
public:
  Fracao() : num(0), den(1) {}                  // sobrecarga de construtor
  Fracao(int n, int d) : num(n), den(d) {}

  Fracao operator+(const Fracao &o) const       // f1 + f2
  { return Fracao(num * o.den + o.num * den, den * o.den); }

  bool operator==(const Fracao &o) const        // f1 == f2
  { return num * o.den == o.num * den; }

  friend ostream &operator<<(ostream &out, const Fracao &f)   // cout << f
  { return out << f.num << "/" << f.den; }
};

int main()
{
  cout << soma(1, 2) << " " << soma(1.5, 2.5) << " " << soma(1, 2, 3) << endl;
  Fracao a(1, 2), b(1, 3), c(2, 4);
  cout << a << " + " << b << " = " << a + b << endl;   // 5/6
  cout << (a == c ? "1/2 == 2/4" : "diferentes") << endl;
  return 0;
}
