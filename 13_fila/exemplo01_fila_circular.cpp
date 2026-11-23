/*
Exemplo 1. Fila estatica circular.
*/
#include <iostream>
using namespace std;

// Fila circular estatica: o primeiro que entra e o primeiro que sai (FIFO)
const int MAX = 5;
struct Fila { int dados[MAX]; int ini, fim, qtd; };

void inicia(Fila &f) { f.ini = f.fim = f.qtd = 0; }
bool vazia(Fila &f) { return f.qtd == 0; }
bool cheia(Fila &f) { return f.qtd == MAX; }

bool enfileira(Fila &f, int x)
{
  if (cheia(f)) return false;
  f.dados[f.fim] = x;
  f.fim = (f.fim + 1) % MAX;   // % faz o indice voltar ao 0 (circular)
  f.qtd++;
  return true;
}

bool desenfileira(Fila &f, int &x)
{
  if (vazia(f)) return false;
  x = f.dados[f.ini];
  f.ini = (f.ini + 1) % MAX;
  f.qtd--;
  return true;
}

int main()
{
  Fila f; int x;
  inicia(f);
  for (int i = 1; i <= 5; i++) enfileira(f, i);
  desenfileira(f, x); desenfileira(f, x);   // libera 2 posicoes no inicio
  enfileira(f, 6); enfileira(f, 7);         // reaproveita as posicoes (circular)
  while (desenfileira(f, x)) cout << x << " ";   // 3 4 5 6 7
  cout << endl;
  return 0;
}
