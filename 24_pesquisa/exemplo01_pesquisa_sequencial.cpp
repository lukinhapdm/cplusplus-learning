/*
Exemplo 1. Pesquisa sequencial: percorre o vetor do inicio ao fim ate achar a chave.
Custo: melhor caso 1 comparacao, pior caso n, caso medio (n+1)/2 quando a chave existe.
*/
#include <iostream>
using namespace std;

const int MAX = 100;

// versao simples: duas comparacoes por passo (fim do vetor e chave)
int sequencial(int v[], int n, int chave, int &comp)
{
  comp = 0;
  for (int i = 0; i < n; i++) {
    comp++;
    if (v[i] == chave) return i;
  }
  return -1;   // nao encontrou
}

// versao com sentinela: coloca a chave na posicao n e elimina o teste de fim do vetor
int sentinela(int v[], int n, int chave, int &comp)
{
  comp = 0;
  v[n] = chave;   // o vetor precisa ter uma posicao livre no final
  int i = 0;
  while (v[i] != chave) { comp++; i++; }
  comp++;
  return i < n ? i : -1;
}

int main()
{
  int v[MAX + 1] = {27, 3, 81, 15, 42, 9, 66, 50};
  int n = 8, comp;

  int p = sequencial(v, n, 42, comp);
  cout << "Sequencial: 42 na posicao " << p << " (" << comp << " comparacoes)" << endl;
  p = sequencial(v, n, 7, comp);
  cout << "Sequencial: 7 na posicao " << p << " (" << comp << " comparacoes)" << endl;

  p = sentinela(v, n, 42, comp);
  cout << "Sentinela: 42 na posicao " << p << " (" << comp << " comparacoes)" << endl;
  p = sentinela(v, n, 7, comp);
  cout << "Sentinela: 7 na posicao " << p << " (" << comp << " comparacoes)" << endl;
  return 0;
}
