/*
Exercicio 1. Medir o numero de comparacoes da forca bruta em tres situacoes, para n = 10000 e m = 10:
(a) texto e padrao aleatorios sobre alfabeto de 26 letras (caso medio, perto de n);
(b) alfabeto binario {a, b} (mais comparacoes, pois casamentos parciais sao mais provaveis);
(c) pior caso: T = aaaa...a e P = aaa...ab, que gasta m comparacoes em cada janela, (n - m + 1) * m.
*/
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

long forcaBruta(const string &T, const string &P)
{
  long comp = 0;
  int n = T.size(), m = P.size();
  for (int i = 0; i <= n - m; i++)
    for (int j = 0; j < m; j++) { comp++; if (T[i + j] != P[j]) break; }
  return comp;
}

string aleatoria(int tam, int c)
{
  string s;
  for (int i = 0; i < tam; i++) s += 'a' + rand() % c;
  return s;
}

int main()
{
  srand(4);
  const int n = 10000, m = 10;
  cout << "Alfabeto 26: " << forcaBruta(aleatoria(n, 26), aleatoria(m, 26)) << " comparacoes" << endl;
  cout << "Alfabeto  2: " << forcaBruta(aleatoria(n, 2), aleatoria(m, 2)) << " comparacoes" << endl;
  string T(n, 'a'), P(m - 1, 'a');
  P += 'b';
  cout << "Pior caso:   " << forcaBruta(T, P) << " comparacoes (formula: " << (long)(n - m + 1) * m << ")" << endl;
  return 0;
}
