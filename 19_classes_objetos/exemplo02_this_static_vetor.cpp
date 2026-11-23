/*
Exemplo 2. Ponteiro this, membro static e vetor de objetos alocados dinamicamente.
*/
#include <iostream>
#include <string>
using namespace std;

class Produto {
private:
  string nome;
  float preco;
  static int total;   // compartilhado por TODOS os objetos
public:
  Produto(string nome, float preco)
  {
    this->nome = nome;     // this diferencia o atributo do parametro
    this->preco = preco;
    total++;
  }
  ~Produto() { total--; }
  void mostra() const { cout << nome << " - R$ " << preco << endl; }
  static int getTotal() { return total; }
};

int Produto::total = 0;   // inicializacao do static fora da classe

int main()
{
  Produto *p1 = new Produto("Caneta", 2.5);
  Produto *p2 = new Produto("Caderno", 15);
  p1->mostra(); p2->mostra();
  cout << "Produtos existentes: " << Produto::getTotal() << endl;   // 2
  delete p1;
  cout << "Produtos existentes: " << Produto::getTotal() << endl;   // 1
  delete p2;
  return 0;
}
