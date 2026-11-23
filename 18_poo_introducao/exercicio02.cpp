/*
Exercicio 2. Classe Lampada com estado ligada/desligada e metodos liga, desliga e mostraEstado.
*/
#include <iostream>
using namespace std;

class Lampada {
private:
  bool ligada = false;   // estado do objeto
public:
  void liga() { ligada = true; }
  void desliga() { ligada = false; }
  void mostraEstado() { cout << (ligada ? "Ligada" : "Desligada") << endl; }
};

int main()
{
  Lampada sala, quarto;   // dois objetos, cada um com seu estado
  sala.liga();
  sala.mostraEstado();    // Ligada
  quarto.mostraEstado();  // Desligada
  return 0;
}
