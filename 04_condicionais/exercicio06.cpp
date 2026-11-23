/*
Exercício 6. Média ponderada (pesos 7, 2 e 1) de 3 notas e conceito A a E, evitando comparações desnecessárias. Fazer teste de mesa.
*/
#include <iostream>
using namespace std;

// Faixas usadas:
// A: >= 8 | B: >= 7 | C: >= 6 | D: >= 5 | E: < 5
int main()
{
  float n1, n2, n3, media;
  cout << "Digite as 3 notas: "; cin >> n1 >> n2 >> n3;
  media = (n1 * 7 + n2 * 2 + n3 * 1) / 10;   // pesos 7, 2 e 1
  cout << "Media: " << media << " - Conceito: ";
  // else if evita testar o limite inferior de novo (ja foi descartado antes)
  if (media >= 8) cout << "A";
  else if (media >= 7) cout << "B";
  else if (media >= 6) cout << "C";
  else if (media >= 5) cout << "D";
  else cout << "E";
  cout << endl;
  return 0;
}
