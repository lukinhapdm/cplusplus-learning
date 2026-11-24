/*
Exemplo 2. Pesquisa binaria: exige vetor ordenado. A cada passo compara com o elemento do meio
e descarta metade do intervalo. Custo O(log n).
*/
#include <iostream>
using namespace std;

// versao iterativa
int binaria(int v[], int n, int chave, int &comp)
{
  int esq = 0, dir = n - 1;
  comp = 0;
  while (esq <= dir) {
    int meio = (esq + dir) / 2;
    comp++;
    if (v[meio] == chave) return meio;
    if (chave < v[meio]) dir = meio - 1;   // continua na metade esquerda
    else esq = meio + 1;                   // continua na metade direita
  }
  return -1;
}

// versao recursiva
int binariaRec(int v[], int esq, int dir, int chave)
{
  if (esq > dir) return -1;   // intervalo vazio
  int meio = (esq + dir) / 2;
  if (v[meio] == chave) return meio;
  if (chave < v[meio]) return binariaRec(v, esq, meio - 1, chave);
  return binariaRec(v, meio + 1, dir, chave);
}

int main()
{
  int v[] = {3, 9, 15, 27, 42, 50, 66, 81, 90, 97};
  int n = 10, comp;

  int p = binaria(v, n, 66, comp);
  cout << "Iterativa: 66 na posicao " << p << " (" << comp << " comparacoes)" << endl;
  p = binaria(v, n, 10, comp);
  cout << "Iterativa: 10 na posicao " << p << " (" << comp << " comparacoes)" << endl;
  cout << "Recursiva: 3 na posicao " << binariaRec(v, 0, n - 1, 3) << endl;
  cout << "Recursiva: 97 na posicao " << binariaRec(v, 0, n - 1, 97) << endl;
  return 0;
}
