/*
Exercicio 1. Troco com o menor numero de moedas. O guloso (sempre a maior moeda que cabe) e otimo para
sistemas "canonicos" como {1, 5, 10, 25, 50, 100}, mas falha em outros, como {1, 3, 4}.
Comparar o guloso com a solucao otima (programacao dinamica) para todos os valores de 1 a 30 e listar
onde o guloso erra.
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int guloso(const vector<int> &moedas, int valor)   // moedas em ordem decrescente
{
  int qtd = 0;
  for (int m : moedas) { qtd += valor / m; valor %= m; }
  return qtd;
}

int otimo(const vector<int> &moedas, int valor)
{
  vector<int> dp(valor + 1, INT_MAX);
  dp[0] = 0;
  for (int v = 1; v <= valor; v++)
    for (int m : moedas)
      if (m <= v && dp[v - m] != INT_MAX && dp[v - m] + 1 < dp[v]) dp[v] = dp[v - m] + 1;
  return dp[valor];
}

void testa(const vector<int> &moedas)
{
  cout << "Moedas {";
  for (size_t i = 0; i < moedas.size(); i++) cout << (i ? ", " : "") << moedas[i];
  cout << "}: ";
  int erros = 0;
  for (int v = 1; v <= 30; v++) {
    int g = guloso(moedas, v), o = otimo(moedas, v);
    if (g != o) { cout << v << "(guloso " << g << ", otimo " << o << ") "; erros++; }
  }
  if (!erros) cout << "guloso sempre otimo";
  cout << endl;
}

int main()
{
  testa({100, 50, 25, 10, 5, 1});
  testa({4, 3, 1});
  testa({10, 7, 1});
  return 0;
}
