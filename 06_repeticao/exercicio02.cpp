/*
Exercício 2. Receber várias idades e mostrar a média; finaliza com idade 0.
*/
#include <iostream>
using namespace std;

int main()
{
  int idade, soma = 0, qtd = 0;
  cout << "Digite as idades (0 para sair):" << endl;
  cin >> idade;
  while (idade != 0) {     // 0 encerra a leitura
    soma += idade;
    qtd++;
    cin >> idade;
  }
  if (qtd > 0) cout << "Media: " << (float) soma / qtd << endl;
  else cout << "Nenhuma idade digitada" << endl;
  return 0;
}
