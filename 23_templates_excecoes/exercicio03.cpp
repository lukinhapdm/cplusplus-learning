/*
Exercicio 3. Ler idade com tratamento de excecoes: lancar excecao se a entrada nao for numero ou se a idade estiver fora de 0 a 130. Repetir ate ler um valor valido.
*/
#include <iostream>
#include <stdexcept>
using namespace std;

int leIdade()
{
  int idade;
  cout << "Idade: ";
  if (!(cin >> idade)) {
    cin.clear();              // limpa o estado de erro do cin
    cin.ignore(1000, '\n');   // descarta o que foi digitado
    throw invalid_argument("Digite apenas numeros");
  }
  if (idade < 0 || idade > 130) throw out_of_range("Idade fora da faixa 0-130");
  return idade;
}

int main()
{
  while (true) {
    try {
      int i = leIdade();
      cout << "Idade valida: " << i << endl;
      break;   // deu certo: sai do laco
    } catch (const exception &e) {   // pega os dois tipos (ambos herdam de exception)
      cout << "Erro: " << e.what() << endl;
    }
  }
  return 0;
}
