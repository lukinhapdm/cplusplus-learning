/*
Exemplo 3. Boyer-Moore-Horspool (BMH): simplificacao do BM que usa so uma tabela de deslocamentos.
Qualquer que seja a posicao da diferenca, a janela e deslocada de acordo com o caractere do texto
alinhado com a ULTIMA posicao do padrao:
    d[c] = m                    se c nao ocorre em P[0..m-2]
    d[c] = m - 1 - j            sendo j a ultima posicao de c em P[0..m-2]
Variante BMHS (Sunday): usa o caractere logo APOS a janela, T[i + m], com
    d[c] = m + 1  ou  m - j (j = ultima posicao de c em P[0..m-1]),
o que permite deslocamentos ainda maiores.
*/
#include <iostream>
#include <string>
using namespace std;

void bmh(const string &T, const string &P)
{
  int n = T.size(), m = P.size(), d[256];
  for (int c = 0; c < 256; c++) d[c] = m;
  for (int j = 0; j < m - 1; j++) d[(unsigned char)P[j]] = m - 1 - j;   // ignora o ultimo caractere de P

  long comp = 0;
  int i = 0;
  while (i <= n - m) {
    int j = m - 1;
    while (j >= 0) { comp++; if (T[i + j] != P[j]) break; j--; }
    if (j < 0) cout << "  BMH: casamento na posicao " << i << endl;
    i += d[(unsigned char)T[i + m - 1]];   // caractere alinhado com o fim do padrao
  }
  cout << "  BMH: " << comp << " comparacoes" << endl;
}

void bmhs(const string &T, const string &P)
{
  int n = T.size(), m = P.size(), d[256];
  for (int c = 0; c < 256; c++) d[c] = m + 1;
  for (int j = 0; j < m; j++) d[(unsigned char)P[j]] = m - j;

  long comp = 0;
  int i = 0;
  while (i <= n - m) {
    int j = m - 1;
    while (j >= 0) { comp++; if (T[i + j] != P[j]) break; j--; }
    if (j < 0) cout << "  BMHS: casamento na posicao " << i << endl;
    if (i + m >= n) break;                 // nao ha caractere depois da janela
    i += d[(unsigned char)T[i + m]];       // caractere logo apos a janela
  }
  cout << "  BMHS: " << comp << " comparacoes" << endl;
}

int main()
{
  string T = "o algoritmo de horspool usa uma tabela de deslocamentos para pular partes do texto";
  string P = "tabela";
  cout << "Tabela d do BMH para \"" << P << "\": ";
  for (int j = 0; j < (int)P.size() - 1; j++) cout << P[j] << "=" << (int)P.size() - 1 - j << " ";
  cout << "outros=" << P.size() << endl;
  bmh(T, P);
  bmhs(T, P);
  return 0;
}
