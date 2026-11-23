/*
Exercício 12. 5 times x 11 jogadores (idade, peso, altura): qtd < 18 anos, média idade por time, média altura geral, % > 80 kg.
*/
#include <iostream>
using namespace std;

int main()
{
  int idade, menores18 = 0, acima80 = 0;
  float peso, altura, somaAlt = 0;
  for (int t = 1; t <= 5; t++) {          // cada time
    int somaIdTime = 0;
    for (int j = 1; j <= 11; j++) {       // cada jogador do time
      cout << "Time " << t << ", jogador " << j << " (idade peso altura): ";
      cin >> idade >> peso >> altura;
      if (idade < 18) menores18++;
      if (peso > 80) acima80++;
      somaIdTime += idade;
      somaAlt += altura;
    }
    cout << "Media de idade do time " << t << ": " << somaIdTime / 11.0 << endl;
  }
  cout << "Jogadores com menos de 18: " << menores18 << endl;
  cout << "Media de altura: " << somaAlt / 55 << endl;          // 5 x 11 = 55
  cout << "% acima de 80 kg: " << acima80 * 100.0 / 55 << "%" << endl;
  return 0;
}
