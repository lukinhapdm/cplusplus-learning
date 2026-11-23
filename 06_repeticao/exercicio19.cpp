/*
Exercício 19. Ler 3 lados > 0; sub-rotinas: verifica se é triângulo e tipo (equilátero/isósceles/escaleno). Mensagens no main.
*/
#include <iostream>
using namespace std;

// cada lado deve ser <= soma dos outros dois
bool ehTriangulo(float a, float b, float c)
{
  return a <= b + c && b <= a + c && c <= a + b;
}

// 0 = equilatero, 1 = isosceles, 2 = escaleno (mensagem fica no main)
int tipo(float a, float b, float c)
{
  if (a == b && b == c) return 0;
  if (a == b || a == c || b == c) return 1;
  return 2;
}

int main()
{
  float a, b, c;
  do { cout << "Tres lados (> 0): "; cin >> a >> b >> c; } while (a <= 0 || b <= 0 || c <= 0);
  if (!ehTriangulo(a, b, c)) cout << "Nao forma triangulo" << endl;
  else {
    int t = tipo(a, b, c);
    if (t == 0) cout << "Equilatero" << endl;
    else if (t == 1) cout << "Isosceles" << endl;
    else cout << "Escaleno" << endl;
  }
  return 0;
}
