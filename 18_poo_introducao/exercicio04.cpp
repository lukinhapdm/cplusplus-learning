/*
Exercicio 4. Classe Pilha (vetor interno de 100 inteiros) com push, pop, top e vazia, escondendo os detalhes de implementacao.
*/
#include <iostream>
using namespace std;

class Pilha {
private:
  int dados[100];
  int topo = 0;
public:
  bool vazia() { return topo == 0; }
  bool push(int x) { if (topo == 100) return false; dados[topo++] = x; return true; }
  int pop() { return dados[--topo]; }    // chame so se nao estiver vazia
  int top() { return dados[topo - 1]; }
};

int main()
{
  Pilha p;   // quem usa nao precisa saber que e um vetor
  for (int i = 1; i <= 3; i++) p.push(i);
  cout << "Topo: " << p.top() << endl;
  while (!p.vazia()) cout << p.pop() << " ";
  cout << endl;
  return 0;
}
