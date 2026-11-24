/*
Exemplo 1. Funcoes de transformacao (hash). Uma boa funcao espalha as chaves uniformemente pela tabela.
- Divisao: h(k) = k mod M (M primo e longe de potencias de 2).
- Multiplicacao: h(k) = floor(M * frac(k * A)), com 0 < A < 1 (Knuth sugere A = (sqrt(5)-1)/2).
- Chaves do tipo string: soma ponderada dos caracteres (metodo polinomial / Horner).
*/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int M = 13;

int hDivisao(int k) { return k % M; }

int hMultiplicacao(int k)
{
  const double A = (sqrt(5.0) - 1) / 2;   // aproximadamente 0.618
  double frac = k * A - floor(k * A);     // parte fracionaria de k*A
  return (int)(M * frac);
}

// h(s) = (s[0]*b^(n-1) + s[1]*b^(n-2) + ... + s[n-1]) mod M, calculado pelo metodo de Horner
int hString(const string &s)
{
  unsigned long h = 0;
  for (char c : s) h = (h * 31 + (unsigned char)c) % M;
  return (int)h;
}

// funcao ruim: so soma os caracteres (anagramas sempre colidem)
int hSoma(const string &s)
{
  int h = 0;
  for (char c : s) h += c;
  return h % M;
}

int main()
{
  int chaves[] = {10, 23, 36, 49, 100, 1234, 4321};
  cout << "chave\tdivisao\tmultiplicacao" << endl;
  for (int k : chaves) cout << k << "\t" << hDivisao(k) << "\t" << hMultiplicacao(k) << endl;
  // 10, 23, 36 e 49 diferem de 13: todas caem na mesma posicao na divisao; a multiplicacao espalha melhor

  string nomes[] = {"amor", "roma", "ramo", "mora", "pedro"};
  cout << "\nstring\tsoma\tpolinomial" << endl;
  for (string s : nomes) cout << s << "\t" << hSoma(s) << "\t" << hString(s) << endl;
  return 0;
}
