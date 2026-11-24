/*
Exemplo 1. Casamento exato com o algoritmo Shift-And (paralelismo de bits).
Ideia: manter um conjunto R com TODOS os prefixos do padrao que casam com o final do texto lido ate agora,
guardado como bits de uma palavra de maquina: o bit j de R indica que P[0..j] casa terminando na posicao atual.
Pre-processamento: para cada caractere c, uma mascara M[c] com o bit j ligado se P[j] == c.
Ao ler o caractere T[i]:
    R = ((R << 1) | 1) & M[T[i]]
(cada prefixo casado cresce um caractere, o "| 1" deixa um casamento novo comecar em i, e o & M[T[i]] mantem
so os prefixos cujo proximo caractere do padrao e T[i]). Se o bit m-1 estiver ligado, P inteiro casou.
Custo O(n) se m <= tamanho da palavra (64 bits aqui), com pre-processamento O(m + c).
Obs.: em Ziviani os bits sao lidos da esquerda para a direita e o deslocamento e ">>"; e a mesma ideia.
*/
#include <iostream>
#include <string>
using namespace std;

void mostraBits(unsigned long long x, int m) { for (int j = 0; j < m; j++) cout << ((x >> j) & 1); }   // bit 0 primeiro

void shiftAnd(const string &T, const string &P, bool rastro)
{
  int n = T.size(), m = P.size();
  unsigned long long M[256] = {0};
  for (int j = 0; j < m; j++) M[(unsigned char)P[j]] |= 1ULL << j;   // pre-processa o padrao

  unsigned long long R = 0, fim = 1ULL << (m - 1);
  for (int i = 0; i < n; i++) {
    R = ((R << 1) | 1) & M[(unsigned char)T[i]];
    if (rastro) { cout << "  " << T[i] << "  R = "; mostraBits(R, m); cout << endl; }
    if (R & fim) cout << "casamento terminando em " << i << " (inicio " << i - m + 1 << ")" << endl;
  }
}

int main()
{
  cout << "Mascaras para P = \"teste\":" << endl;
  string P = "teste";
  for (char c : string("tes")) {
    unsigned long long mask = 0;
    for (int j = 0; j < (int)P.size(); j++) if (P[j] == c) mask |= 1ULL << j;
    cout << "  M['" << c << "'] = "; mostraBits(mask, P.size()); cout << endl;
  }
  cout << "Rastro em \"os testes\":" << endl;
  shiftAnd("os testes", P, true);

  cout << "\nPadrao \"ana\" em \"banana bacana\":" << endl;
  shiftAnd("banana bacana", "ana", false);
  return 0;
}
