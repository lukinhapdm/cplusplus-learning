/*
Exercicio 3. Em um vetor ordenado com repeticoes, usar pesquisa binaria para achar a primeira e a
ultima ocorrencia de uma chave e, com isso, contar quantas vezes ela aparece em O(log n).
*/
#include <iostream>
using namespace std;

// primeira posicao com v[i] >= chave
int limiteInferior(int v[], int n, int chave)
{
  int esq = 0, dir = n;   // intervalo [esq, dir)
  while (esq < dir) {
    int meio = (esq + dir) / 2;
    if (v[meio] < chave) esq = meio + 1;
    else dir = meio;
  }
  return esq;
}

// primeira posicao com v[i] > chave
int limiteSuperior(int v[], int n, int chave)
{
  int esq = 0, dir = n;
  while (esq < dir) {
    int meio = (esq + dir) / 2;
    if (v[meio] <= chave) esq = meio + 1;
    else dir = meio;
  }
  return esq;
}

int main()
{
  int v[] = {1, 3, 3, 3, 5, 7, 7, 9, 9, 9, 9, 12};
  int n = 12;
  int chaves[] = {3, 9, 4, 12};
  for (int c : chaves) {
    int ini = limiteInferior(v, n, c), fim = limiteSuperior(v, n, c);
    if (ini == fim) cout << c << ": nao existe (seria inserido na posicao " << ini << ")" << endl;
    else cout << c << ": posicoes " << ini << " a " << fim - 1 << ", aparece " << fim - ini << " vezes" << endl;
  }
  return 0;
}
