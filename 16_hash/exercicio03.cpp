/*
Exercicio 3. Usando hash, contar quantas vezes cada numero aparece em uma sequencia (termina com -1).
*/
#include <iostream>
using namespace std;

const int TAM = 17;
struct No { int chave, qtd; No *prox; };

int h(int k) { return (k % TAM + TAM) % TAM; }   // funciona tambem para negativos

void conta(No *t[], int k)
{
  for (No *a = t[h(k)]; a; a = a->prox)
    if (a->chave == k) { a->qtd++; return; }   // ja existe: so soma
  t[h(k)] = new No{k, 1, t[h(k)]};             // primeira vez
}

int main()
{
  No *t[TAM] = {nullptr}; int x;
  cout << "Numeros (-1 encerra): ";
  while (cin >> x && x != -1) conta(t, x);
  for (int i = 0; i < TAM; i++)
    for (No *a = t[i]; a; a = a->prox) cout << a->chave << " aparece " << a->qtd << "x" << endl;
  return 0;
}
