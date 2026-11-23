/*
Exemplo 3. Construtor de copia e operador de atribuicao (regra dos tres) para classes que alocam memoria.
*/
#include <iostream>
using namespace std;

class Vetor {
  int *dados;
  int tam;
public:
  Vetor(int n) : tam(n) { dados = new int[n](); }
  ~Vetor() { delete[] dados; }

  // sem isto, a copia dividiria o MESMO ponteiro e o delete aconteceria duas vezes
  Vetor(const Vetor &o) : tam(o.tam)
  {
    dados = new int[tam];                          // memoria propria
    for (int i = 0; i < tam; i++) dados[i] = o.dados[i];
  }

  Vetor &operator=(const Vetor &o)
  {
    if (this == &o) return *this;                  // v = v
    delete[] dados;                                // descarta o antigo
    tam = o.tam;
    dados = new int[tam];
    for (int i = 0; i < tam; i++) dados[i] = o.dados[i];
    return *this;
  }

  void set(int i, int v) { dados[i] = v; }
  int get(int i) const { return dados[i]; }
};

int main()
{
  Vetor a(3);
  a.set(0, 10);
  Vetor b = a;     // construtor de copia
  b.set(0, 99);    // altera so a copia
  Vetor c(1);
  c = a;           // operador de atribuicao
  cout << a.get(0) << " " << b.get(0) << " " << c.get(0) << endl;   // 10 99 10
  return 0;
}
