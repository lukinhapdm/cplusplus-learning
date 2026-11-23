/*
Exercicio 4. Hash com sondagem linear: inserir chaves e mostrar quantas colisoes ocorreram e o fator de carga.
*/
#include <iostream>
using namespace std;

const int TAM = 10;

int main()
{
  int t[TAM], n, chave, colisoes = 0, ocupados = 0;
  for (int i = 0; i < TAM; i++) t[i] = -1;
  cout << "Quantas chaves (max 10)? "; cin >> n;
  for (int k = 0; k < n; k++) {
    cin >> chave;
    int p = chave % TAM;
    while (t[p] != -1) { colisoes++; p = (p + 1) % TAM; }   // cada passo extra = colisao
    t[p] = chave; ocupados++;
  }
  for (int i = 0; i < TAM; i++) cout << i << ": " << t[i] << endl;
  cout << "Colisoes: " << colisoes << endl;
  cout << "Fator de carga: " << (float) ocupados / TAM << endl;   // ocupacao da tabela
  return 0;
}
