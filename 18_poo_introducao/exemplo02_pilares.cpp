/*
Exemplo 2. Os 4 pilares da POO em um exemplo curto: abstracao, encapsulamento, heranca e polimorfismo.
*/
#include <iostream>
#include <string>
using namespace std;

// Abstracao: so o que importa de um animal para o programa
class Animal {
protected:          // Encapsulamento: acessivel so pela classe e filhas
  string nome;
public:
  Animal(string n) : nome(n) {}
  virtual void som() { cout << nome << " faz algum som" << endl; }
  virtual ~Animal() {}
};

// Heranca: Cachorro e um Animal
class Cachorro : public Animal {
public:
  Cachorro(string n) : Animal(n) {}
  void som() override { cout << nome << " late" << endl; }   // Polimorfismo
};

class Gato : public Animal {
public:
  Gato(string n) : Animal(n) {}
  void som() override { cout << nome << " mia" << endl; }
};

int main()
{
  Animal *bichos[3] = {new Animal("Generico"), new Cachorro("Rex"), new Gato("Mimi")};
  for (int i = 0; i < 3; i++) { bichos[i]->som(); delete bichos[i]; }   // cada um responde do seu jeito
  return 0;
}
