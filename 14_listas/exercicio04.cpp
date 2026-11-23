/*
Exercicio 4. Lista duplamente encadeada: inserir no fim e imprimir do inicio para o fim e do fim para o inicio.
*/
#include <iostream>
using namespace std;

// cada no conhece o anterior e o proximo
struct No { int valor; No *ant, *prox; };
struct ListaD { No *ini, *fim; };

void insereFim(ListaD &l, int x)
{
  No *n = new No; n->valor = x; n->prox = nullptr; n->ant = l.fim;
  if (l.fim == nullptr) l.ini = n; else l.fim->prox = n;
  l.fim = n;
}

int main()
{
  ListaD l = {nullptr, nullptr};
  for (int i = 1; i <= 5; i++) insereFim(l, i);
  for (No *a = l.ini; a; a = a->prox) cout << a->valor << " ";   // ida
  cout << endl;
  for (No *a = l.fim; a; a = a->ant) cout << a->valor << " ";    // volta
  cout << endl;
  while (l.ini) { No *a = l.ini; l.ini = a->prox; delete a; }    // libera
  return 0;
}
