/*
Exemplo 1. Template de funcao e template de classe (Pilha generica).
*/
#include <iostream>
#include <string>
using namespace std;

// funciona para qualquer tipo que tenha o operador >
template <typename T>
T maior(T a, T b) { return a > b ? a : b; }

template <typename T>
class Pilha {
  T dados[100];
  int topo = 0;
public:
  void push(T x) { dados[topo++] = x; }
  T pop() { return dados[--topo]; }
  bool vazia() const { return topo == 0; }
};

int main()
{
  cout << maior(3, 7) << " " << maior(2.5, 1.5) << " " << maior<string>("ana", "bia") << endl;
  Pilha<char> p;   // o tipo e escolhido na hora de usar
  for (char c : string("abc")) p.push(c);
  while (!p.vazia()) cout << p.pop();
  cout << endl;
  return 0;
}
