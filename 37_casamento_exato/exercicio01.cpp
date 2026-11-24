/*
Exercicio 1. Comparar o numero de comparacoes de caracteres da forca bruta, do BMH e do BMHS em um texto
aleatorio grande (n = 100000) para padroes de tamanho m = 2, 5, 10 e 20. Repetir com alfabeto binario.
Observar que os metodos de Boyer-Moore melhoram com m grande e alfabeto grande (deslocamentos maiores).
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

long bmh(const string &T, const string &P)
{
  int n = T.size(), m = P.size(), d[256];
  long comp = 0;
  for (int c = 0; c < 256; c++) d[c] = m;
  for (int j = 0; j < m - 1; j++) d[(unsigned char)P[j]] = m - 1 - j;
  for (int i = 0; i <= n - m; i += d[(unsigned char)T[i + m - 1]])
    for (int j = m - 1; j >= 0; j--) { comp++; if (T[i + j] != P[j]) break; }
  return comp;
}

long bmhs(const string &T, const string &P)
{
  int n = T.size(), m = P.size(), d[256];
  long comp = 0;
  for (int c = 0; c < 256; c++) d[c] = m + 1;
  for (int j = 0; j < m; j++) d[(unsigned char)P[j]] = m - j;
  for (int i = 0; i <= n - m;) {
    for (int j = m - 1; j >= 0; j--) { comp++; if (T[i + j] != P[j]) break; }
    if (i + m >= n) break;
    i += d[(unsigned char)T[i + m]];
  }
  return comp;
}

string aleatoria(int tam, int c) { string s; for (int i = 0; i < tam; i++) s += 'a' + rand() % c; return s; }

int main()
{
  srand(8);
  for (int c : {26, 2}) {
    string T = aleatoria(100000, c);
    cout << "Alfabeto com " << c << " simbolos:" << endl;
    cout << "  m\tforca bruta\tBMH\tBMHS" << endl;
    for (int m : {2, 5, 10, 20}) {
      string P = T.substr(50000, m);   // padrao que ocorre ao menos uma vez
      cout << "  " << m << "\t" << forcaBruta(T, P) << "\t\t" << bmh(T, P) << "\t" << bmhs(T, P) << endl;
    }
  }
  return 0;
}
