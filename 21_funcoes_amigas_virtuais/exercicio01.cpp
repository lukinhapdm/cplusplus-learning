/*
Exercicio 1. Classe Complexo com funcao amiga para somar dois complexos e outra para imprimir.
*/
#include <iostream>
using namespace std;

class Complexo {
  double re, im;
public:
  Complexo(double r = 0, double i = 0) : re(r), im(i) {}
  friend Complexo soma(const Complexo &a, const Complexo &b);
  friend void imprime(const Complexo &c);
};

// por ser amiga, acessa re e im diretamente
Complexo soma(const Complexo &a, const Complexo &b) { return Complexo(a.re + b.re, a.im + b.im); }
void imprime(const Complexo &c) { cout << c.re << (c.im >= 0 ? " + " : " - ") << (c.im >= 0 ? c.im : -c.im) << "i" << endl; }

int main()
{
  Complexo a(2, 3), b(1, -5);
  imprime(soma(a, b));   // 3 - 2i
  return 0;
}
