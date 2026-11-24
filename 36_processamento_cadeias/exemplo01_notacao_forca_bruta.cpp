/*
Exemplo 1. Processamento de cadeias de caracteres: notacao e algoritmo forca bruta.
Notacao:
  - alfabeto (Sigma): conjunto finito de simbolos (ex.: {0,1}, {A,C,G,T}, ASCII); c = |Sigma|;
  - texto T[0..n-1] e padrao P[0..m-1], com m <= n;
  - casamento de cadeias: encontrar todas as posicoes i em que P ocorre em T (T[i..i+m-1] == P).
Categorias de algoritmos (conforme o que e pre-processado):
  1) nem padrao nem texto: forca bruta, O(nm) no pior caso;
  2) so o padrao: Shift-And, KMP, Boyer-Moore, BMH... O(n) a O(nm), varrem o texto todo a cada consulta;
  3) padrao e texto: o texto ganha um indice (arquivo invertido, arvore/arranjo de sufixos) e as
     consultas ficam muito mais rapidas, a custo de espaco e de tempo para construir o indice.
Forca bruta: tenta casar P em cada posicao i do texto, comparando da esquerda para a direita.
*/
#include <iostream>
#include <string>
using namespace std;

int forcaBruta(const string &T, const string &P, long &comparacoes)
{
  int n = T.size(), m = P.size(), ocorrencias = 0;
  comparacoes = 0;
  for (int i = 0; i <= n - m; i++) {   // cada janela do texto
    int j = 0;
    while (j < m) {
      comparacoes++;
      if (T[i + j] != P[j]) break;      // desistiu desta janela
      j++;
    }
    if (j == m) { cout << "  casamento na posicao " << i << endl; ocorrencias++; }
  }
  return ocorrencias;
}

int main()
{
  string T = "abracadabra, disse a abracadabrante cabra";
  string P = "abra";
  long comp;
  cout << "Texto: \"" << T << "\" (n = " << T.size() << ")" << endl;
  cout << "Padrao: \"" << P << "\" (m = " << P.size() << ")" << endl;
  int occ = forcaBruta(T, P, comp);
  cout << occ << " ocorrencias, " << comp << " comparacoes de caracteres" << endl;
  return 0;
}
