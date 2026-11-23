/*
Exercicio 4. Classe Fila dinamica (encadeada) com construtor, destrutor, enfileira, desenfileira e tamanho.
*/
#include <iostream>
using namespace std;

class Fila {
private:
  struct No { int valor; No *prox; };   // struct interna, escondida de fora
  No *ini = nullptr, *fim = nullptr;
  int n = 0;
public:
  ~Fila() { int x; while (desenfileira(x)); }   // esvazia ao destruir

  void enfileira(int x)
  {
    No *novo = new No{x, nullptr};
    if (fim) fim->prox = novo; else ini = novo;
    fim = novo; n++;
  }
  bool desenfileira(int &x)
  {
    if (!ini) return false;
    No *a = ini; x = a->valor; ini = a->prox;
    if (!ini) fim = nullptr;
    delete a; n--;
    return true;
  }
  int tamanho() const { return n; }
};

int main()
{
  Fila f; int x;
  for (int i = 1; i <= 4; i++) f.enfileira(i * 5);
  cout << "Tamanho: " << f.tamanho() << endl;
  while (f.desenfileira(x)) cout << x << " ";
  cout << endl;
  return 0;
}
