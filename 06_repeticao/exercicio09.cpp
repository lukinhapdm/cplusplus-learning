/*
Exercício 9. Ler inteiros positivos até 0; mostrar maior e menor; avisar negativos (fora dos cálculos).
*/
#include <iostream>
using namespace std;

int main()
{
  int v, maior = 0, menor = 0;
  bool primeiro = true;   // o primeiro valor valido vira maior e menor
  cout << "Digite valores (0 para sair):" << endl;
  cin >> v;
  while (v != 0) {
    if (v < 0) cout << "Valor negativo ignorado" << endl;
    else {
      if (primeiro || v > maior) maior = v;
      if (primeiro || v < menor) menor = v;
      primeiro = false;
    }
    cin >> v;
  }
  if (!primeiro) cout << "Maior: " << maior << " | Menor: " << menor << endl;
  return 0;
}
