/*
Exemplo 2. Backtracking (tentativa e erro): constroi a solucao passo a passo e, assim que uma escolha
parcial viola alguma restricao, desiste dela e volta (backtrack) para tentar a proxima alternativa.
Equivale a uma busca em profundidade na arvore de solucoes parciais, com poda dos ramos invalidos.
Problema das n rainhas: colocar n rainhas num tabuleiro n x n sem que duas se ataquem.
Uma rainha por linha; para a linha l testa cada coluna c livre (coluna e diagonais nao atacadas).
*/
#include <iostream>
using namespace std;

const int MAX = 12;
int n, col[MAX];                                    // col[l] = coluna da rainha da linha l
bool usadaCol[MAX], usadaDiag1[2 * MAX], usadaDiag2[2 * MAX];
long long nos, solucoes;

void imprime()
{
  for (int l = 0; l < n; l++) {
    for (int c = 0; c < n; c++) cout << (col[l] == c ? " Q" : " .");
    cout << endl;
  }
}

void coloca(int l)
{
  nos++;
  if (l == n) {   // todas as linhas preenchidas: solucao
    if (++solucoes == 1 && n == 8) imprime();   // mostra so a primeira do caso 8x8
    return;
  }
  for (int c = 0; c < n; c++) {
    if (usadaCol[c] || usadaDiag1[l + c] || usadaDiag2[l - c + n]) continue;   // poda
    col[l] = c;
    usadaCol[c] = usadaDiag1[l + c] = usadaDiag2[l - c + n] = true;    // faz a escolha
    coloca(l + 1);
    usadaCol[c] = usadaDiag1[l + c] = usadaDiag2[l - c + n] = false;   // desfaz (backtrack)
  }
}

int main()
{
  for (n = 4; n <= 10; n++) {
    nos = solucoes = 0;
    if (n == 8) cout << "Primeira solucao para 8 rainhas:" << endl;
    coloca(0);
    long long forca = 1;
    for (int i = 0; i < n; i++) forca *= n;   // forca bruta: n^n posicionamentos (uma por linha)
    cout << "n = " << n << ": " << solucoes << " solucoes, " << nos << " nos visitados (forca bruta: " << forca << ")" << endl;
  }
  return 0;
}
