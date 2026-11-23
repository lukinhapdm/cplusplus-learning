/*
Exemplo 2. TAD Ponto: o usuario so usa as funcoes, sem mexer direto nos campos.
*/
#include <iostream>
#include <cmath>
using namespace std;

// TAD = dados + operacoes sobre esses dados
struct Ponto { float x, y; };

Ponto *criaPonto(float x, float y)
{
  Ponto *p = new Ponto;   // aloca dinamicamente
  p->x = x;               // -> acessa campo via ponteiro
  p->y = y;
  return p;
}

void liberaPonto(Ponto *p) { delete p; }

float distancia(Ponto *a, Ponto *b)
{
  float dx = a->x - b->x, dy = a->y - b->y;
  return sqrt(dx * dx + dy * dy);
}

int main()
{
  Ponto *a = criaPonto(0, 0);
  Ponto *b = criaPonto(3, 4);
  cout << "Distancia: " << distancia(a, b) << endl;   // 5
  liberaPonto(a);
  liberaPonto(b);
  return 0;
}
