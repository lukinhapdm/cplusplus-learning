/*
Exercicio 1. Implementar o TAD Conjunto para elementos de 0 a 63 usando um vetor de bits (um unsigned long long):
o bit i ligado significa que i pertence ao conjunto. Uniao, intersecao e diferenca viram operacoes
bit a bit (|, &, & ~) feitas em O(1).
*/
#include <iostream>
using namespace std;

class ConjuntoBits {
  unsigned long long bits = 0;
  ConjuntoBits(unsigned long long b) : bits(b) {}
public:
  ConjuntoBits() {}
  void insere(int x) { bits |= (1ULL << x); }
  void remove(int x) { bits &= ~(1ULL << x); }
  bool pertence(int x) const { return (bits >> x) & 1; }
  ConjuntoBits uniao(const ConjuntoBits &o) const { return ConjuntoBits(bits | o.bits); }
  ConjuntoBits intersecao(const ConjuntoBits &o) const { return ConjuntoBits(bits & o.bits); }
  ConjuntoBits diferenca(const ConjuntoBits &o) const { return ConjuntoBits(bits & ~o.bits); }
  bool subconjunto(const ConjuntoBits &o) const { return (bits & o.bits) == bits; }

  int tamanho() const
  {
    int c = 0;
    for (unsigned long long b = bits; b; b &= b - 1) c++;   // b & (b-1) apaga o bit 1 mais baixo
    return c;
  }

  void imprime() const
  {
    cout << "{ ";
    for (int i = 0; i < 64; i++) if (pertence(i)) cout << i << " ";
    cout << "} (" << tamanho() << " elementos)" << endl;
  }
};

int main()
{
  ConjuntoBits pares, primos;
  for (int i = 0; i < 20; i += 2) pares.insere(i);
  for (int p : {2, 3, 5, 7, 11, 13, 17, 19}) primos.insere(p);
  cout << "Pares:      "; pares.imprime();
  cout << "Primos:     "; primos.imprime();
  cout << "Uniao:      "; pares.uniao(primos).imprime();
  cout << "Intersecao: "; pares.intersecao(primos).imprime();
  cout << "Primos - pares: "; primos.diferenca(pares).imprime();
  cout << "Intersecao contida em pares? " << pares.intersecao(primos).subconjunto(pares) << endl;
  return 0;
}
