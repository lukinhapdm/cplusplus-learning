/*
Exercicio 2. Estender o Shift-And para padroes com classes de caracteres, mudando so o pre-processamento:
  - '?'      casa com qualquer caractere (o bit j fica ligado em TODAS as mascaras);
  - [abc]    casa com a, b ou c (o bit j fica ligado em M['a'], M['b'] e M['c']).
O laco de busca continua identico. Ex.: "c[aeo]s?" encontra "casa", "cest" (de cesto), "cosm"...
*/
#include <iostream>
#include <string>
using namespace std;

// devolve o tamanho logico do padrao (quantas posicoes) e preenche as mascaras
int preProcessa(const string &P, unsigned long long M[256])
{
  for (int c = 0; c < 256; c++) M[c] = 0;
  int j = 0;
  for (size_t k = 0; k < P.size(); k++, j++) {
    if (P[k] == '?') {
      for (int c = 0; c < 256; c++) M[c] |= 1ULL << j;
    } else if (P[k] == '[') {
      for (k++; k < P.size() && P[k] != ']'; k++) M[(unsigned char)P[k]] |= 1ULL << j;
    } else {
      M[(unsigned char)P[k]] |= 1ULL << j;
    }
  }
  return j;
}

void busca(const string &T, const string &P)
{
  unsigned long long M[256];
  int m = preProcessa(P, M);
  unsigned long long R = 0, fim = 1ULL << (m - 1);
  cout << "\"" << P << "\" (m = " << m << "): ";
  for (int i = 0; i < (int)T.size(); i++) {
    R = ((R << 1) | 1) & M[(unsigned char)T[i]];
    if (R & fim) cout << T.substr(i - m + 1, m) << "@" << i - m + 1 << "  ";
  }
  cout << endl;
}

int main()
{
  string T = "a casa do cosmonauta tem um cesto e uma cisterna";
  busca(T, "c[aeo]s?");
  busca(T, "c?s");
  busca(T, "[ct]e[ms]");
  return 0;
}
