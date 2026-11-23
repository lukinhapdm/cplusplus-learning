/*
Exercício 11. Ler idade e sexo até entrada inválida; mostrar média geral, das mulheres e dos homens.
*/
#include <iostream>
using namespace std;

int main()
{
  int idade, somaT = 0, qtdT = 0, somaF = 0, qtdF = 0, somaM = 0, qtdM = 0;
  char sexo;
  while (true) {
    cout << "Idade e sexo (f/m): "; cin >> idade >> sexo;
    if (idade <= 0 || (sexo != 'f' && sexo != 'm')) break;   // entrada invalida encerra
    somaT += idade; qtdT++;
    if (sexo == 'f') { somaF += idade; qtdF++; }
    else { somaM += idade; qtdM++; }
  }
  // so divide se houver pessoas no grupo
  if (qtdT) cout << "Media geral: " << (float) somaT / qtdT << endl;
  if (qtdF) cout << "Media mulheres: " << (float) somaF / qtdF << endl;
  if (qtdM) cout << "Media homens: " << (float) somaM / qtdM << endl;
  return 0;
}
