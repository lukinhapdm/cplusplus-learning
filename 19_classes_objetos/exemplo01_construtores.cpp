/*
Exemplo 1. Construtor padrao, construtor com parametros, lista de inicializacao e destrutor.
*/
#include <iostream>
#include <string>
using namespace std;

class Aluno {
private:
  string nome;
  float nota;
public:
  Aluno() : nome("Sem nome"), nota(0) { cout << "Construtor padrao" << endl; }
  Aluno(string n, float x) : nome(n), nota(x) { cout << "Construtor de " << nome << endl; }
  ~Aluno() { cout << "Destruindo " << nome << endl; }   // chamado ao sair do escopo

  // getters e setters
  string getNome() const { return nome; }   // const: nao altera o objeto
  float getNota() const { return nota; }
  void setNota(float x) { if (x >= 0 && x <= 10) nota = x; }
};

int main()
{
  Aluno a;
  Aluno b("Ana", 8.5);
  b.setNota(11);   // ignorado: fora da faixa
  cout << b.getNome() << ": " << b.getNota() << endl;
  return 0;
}
