/*
Exemplo 1. Tabela hash com enderecamento aberto (sondagem linear).
*/
#include <iostream>
using namespace std;

const int TAM = 11;
const int VAZIO = -1;

int h(int chave) { return chave % TAM; }   // funcao hash: resto da divisao

void inicia(int t[]) { for (int i = 0; i < TAM; i++) t[i] = VAZIO; }

bool insere(int t[], int chave)
{
  int pos = h(chave);
  for (int i = 0; i < TAM; i++) {
    int p = (pos + i) % TAM;   // colisao: tenta a proxima posicao
    if (t[p] == VAZIO) { t[p] = chave; return true; }
  }
  return false;   // tabela cheia
}

int busca(int t[], int chave)
{
  int pos = h(chave);
  for (int i = 0; i < TAM; i++) {
    int p = (pos + i) % TAM;
    if (t[p] == VAZIO) return -1;   // achou vazio: chave nao existe
    if (t[p] == chave) return p;
  }
  return -1;
}

int main()
{
  int t[TAM]; inicia(t);
  int v[] = {22, 33, 15, 4, 44};   // 22, 33 e 44 colidem na posicao 0
  for (int x : v) insere(t, x);
  for (int i = 0; i < TAM; i++) cout << i << ": " << t[i] << endl;
  cout << "33 esta na posicao " << busca(t, 33) << endl;
  return 0;
}
