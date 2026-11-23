/*
Exercicio 4. Template de classe Vetor<T> com tamanho fixo e metodo at(i) que lanca out_of_range quando o indice e invalido.
*/
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class Vetor {
  T *dados;
  int tam;
public:
  Vetor(int n) : tam(n) { dados = new T[n](); }   // () zera os valores
  ~Vetor() { delete[] dados; }

  T &at(int i)
  {
    if (i < 0 || i >= tam) throw out_of_range("Indice " + to_string(i) + " invalido");
    return dados[i];   // devolve referencia: permite ler e alterar
  }
  int tamanho() const { return tam; }
};

int main()
{
  Vetor<double> v(3);
  try {
    v.at(0) = 1.5;
    v.at(2) = 3.5;
    cout << v.at(0) << " " << v.at(2) << endl;
    v.at(5) = 10;   // lanca excecao
  } catch (const out_of_range &e) {
    cout << "Erro: " << e.what() << endl;
  }
  return 0;
}
