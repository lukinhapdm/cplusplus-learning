/*
Exemplo 2. Algoritmo de Boyer-Moore (BM). Compara o padrao com o texto da DIREITA para a ESQUERDA dentro
da janela; quando ha diferenca, desloca a janela pelo maior valor dado por duas heuristicas:
  - ocorrencia (caractere ruim): alinha o caractere do texto que causou a diferenca com a sua ultima
    ocorrencia no padrao (ou pula o padrao inteiro se ele nao ocorre em P);
  - casamento (sufixo bom): o trecho que ja casou (sufixo de P) e alinhado com outra ocorrencia dele em P,
    ou com o maior prefixo de P que e sufixo desse trecho.
No caso medio e sublinear (pode pular caracteres do texto); no pior caso O(nm) nesta forma simples.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ultima posicao de cada caractere no padrao (-1 se nao ocorre)
void tabelaOcorrencia(const string &P, int ult[256])
{
  for (int c = 0; c < 256; c++) ult[c] = -1;
  for (int j = 0; j < (int)P.size(); j++) ult[(unsigned char)P[j]] = j;
}

// d[j] = deslocamento quando P[j+1..m-1] casou e P[j] falhou (j = -1 significa casamento completo)
vector<int> tabelaSufixoBom(const string &P)
{
  int m = P.size();
  vector<int> borda(m + 1), d(m + 1, 0);
  // borda[i]: inicio da maior borda de P[i..m-1] (sufixo de P[i..] que tambem e prefixo de P[i..])
  int i = m, j = m + 1;
  borda[i] = j;
  while (i > 0) {
    while (j <= m && P[i - 1] != P[j - 1]) {
      if (d[j] == 0) d[j] = j - i;   // caso 1: o sufixo bom ocorre mais a esquerda em P
      j = borda[j];
    }
    i--; j--;
    borda[i] = j;
  }
  j = borda[0];
  for (i = 0; i <= m; i++) {           // caso 2: so um prefixo de P casa com parte do sufixo bom
    if (d[i] == 0) d[i] = j;
    if (i == j) j = borda[j];
  }
  return d;   // d[j+1] e o deslocamento para falha na posicao j
}

void boyerMoore(const string &T, const string &P)
{
  int n = T.size(), m = P.size(), ult[256];
  tabelaOcorrencia(P, ult);
  vector<int> d = tabelaSufixoBom(P);
  long comp = 0;
  int i = 0;   // inicio da janela no texto
  while (i <= n - m) {
    int j = m - 1;
    while (j >= 0) {   // compara da direita para a esquerda
      comp++;
      if (P[j] != T[i + j]) break;
      j--;
    }
    if (j < 0) {
      cout << "  casamento na posicao " << i << endl;
      i += d[0];
    } else {
      int pOcorrencia = j - ult[(unsigned char)T[i + j]];   // pode ser <= 0
      int pSufixo = d[j + 1];
      i += max(pOcorrencia, pSufixo);
    }
  }
  cout << "  comparacoes: " << comp << " (n = " << n << ")" << endl;
}

int main()
{
  string T = "aqui procuramos o padrao exemplo dentro de um texto com mais um exemplo no fim";
  cout << "Padrao \"exemplo\":" << endl;
  boyerMoore(T, "exemplo");
  cout << "Padrao \"abcab\" em \"abcabcabxabcab\":" << endl;
  boyerMoore("abcabcabxabcab", "abcab");
  return 0;
}
