/*
Exercicio 2. Pesquisa sequencial auto-organizavel. Implementar duas estrategias:
(a) mover para frente: o elemento encontrado vai para a posicao 0;
(b) transposicao: o elemento encontrado troca de lugar com o anterior.
Fazer varias buscas repetidas e comparar o total de comparacoes.
*/
#include <iostream>
using namespace std;

int moverFrente(int v[], int n, int chave, int &comp)
{
  for (int i = 0; i < n; i++) {
    comp++;
    if (v[i] == chave) {
      for (int j = i; j > 0; j--) v[j] = v[j - 1];   // desloca para abrir espaco
      v[0] = chave;
      return 0;
    }
  }
  return -1;
}

int transposicao(int v[], int n, int chave, int &comp)
{
  for (int i = 0; i < n; i++) {
    comp++;
    if (v[i] == chave) {
      if (i > 0) { int aux = v[i]; v[i] = v[i - 1]; v[i - 1] = aux; return i - 1; }
      return 0;
    }
  }
  return -1;
}

void imprime(int v[], int n) { for (int i = 0; i < n; i++) cout << v[i] << " "; cout << endl; }

int main()
{
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int b[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int buscas[] = {8, 8, 7, 8, 8, 7, 8, 6, 8, 8};   // 8 e muito mais procurado
  int compA = 0, compB = 0;
  for (int c : buscas) { moverFrente(a, 8, c, compA); transposicao(b, 8, c, compB); }
  cout << "Mover para frente: " << compA << " comparacoes -> "; imprime(a, 8);
  cout << "Transposicao:      " << compB << " comparacoes -> "; imprime(b, 8);
  cout << "Sem reorganizar:   " << 7 * 8 + 2 * 7 + 6 << " comparacoes" << endl;
  return 0;
}
