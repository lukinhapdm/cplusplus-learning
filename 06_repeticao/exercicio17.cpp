/*
Exercício 17. Função que lê salário e nº de filhos (qtd indeterminada) e retorna: média salário, média filhos, maior salário, % salário < R$380.
*/
#include <iostream>
using namespace std;

// varios resultados: devolvidos por referencia
void pesquisa(float &mediaSal, float &mediaFilhos, float &maiorSal, float &percBaixo)
{
  float sal, soma = 0; int filhos, somaF = 0, qtd = 0, baixo = 0;
  maiorSal = 0;
  cout << "Salario e filhos (salario negativo encerra):" << endl;
  while (cin >> sal && sal >= 0) {
    cin >> filhos;
    soma += sal; somaF += filhos; qtd++;
    if (sal > maiorSal) maiorSal = sal;
    if (sal < 380) baixo++;
  }
  mediaSal = qtd ? soma / qtd : 0;
  mediaFilhos = qtd ? (float) somaF / qtd : 0;
  percBaixo = qtd ? baixo * 100.0 / qtd : 0;
}

int main()
{
  float ms, mf, maior, perc;
  pesquisa(ms, mf, maior, perc);
  cout << "Media salario: " << ms << "\nMedia filhos: " << mf
       << "\nMaior salario: " << maior << "\n% abaixo de R$380: " << perc << endl;
  return 0;
}
