/*
Exercicio 2. Template de classe Par<T1, T2> que guarda dois valores de tipos diferentes, com getters e metodo mostra.
*/
#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class Par {
  T1 primeiro;
  T2 segundo;
public:
  Par(T1 a, T2 b) : primeiro(a), segundo(b) {}
  T1 getPrimeiro() const { return primeiro; }
  T2 getSegundo() const { return segundo; }
  void mostra() const { cout << "(" << primeiro << ", " << segundo << ")" << endl; }
};

int main()
{
  Par<string, int> aluno("Ana", 20);
  Par<char, double> nota('A', 9.5);
  aluno.mostra();
  nota.mostra();
  cout << aluno.getPrimeiro() << " tem " << aluno.getSegundo() << " anos" << endl;
  return 0;
}
