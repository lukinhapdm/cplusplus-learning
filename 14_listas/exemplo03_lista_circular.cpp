/*
Exemplo 3. Lista circular encadeada: o ultimo no aponta de volta para o primeiro.
*/
#include <iostream>
using namespace std;

struct No { int valor; No *prox; };

// guardamos so o ultimo: ultimo->prox e o primeiro
void insereFim(No *&ult, int x)
{
  No *n = new No; n->valor = x;
  if (ult == nullptr) n->prox = n;                 // um so no aponta para ele mesmo
  else { n->prox = ult->prox; ult->prox = n; }     // entra entre o ultimo e o primeiro
  ult = n;
}

void imprime(No *ult)
{
  if (!ult) return;
  No *a = ult->prox;                    // comeca no primeiro
  do { cout << a->valor << " "; a = a->prox; } while (a != ult->prox);   // para ao dar a volta
  cout << endl;
}

void libera(No *&ult)
{
  if (!ult) return;
  No *a = ult->prox;
  ult->prox = nullptr;                  // quebra o circulo para poder parar
  while (a) { No *t = a; a = a->prox; delete t; }
  ult = nullptr;
}

int main()
{
  No *ult = nullptr;
  for (int i = 1; i <= 5; i++) insereFim(ult, i);
  imprime(ult);   // 1 2 3 4 5
  // percorrer 12 passos mostra que a lista "da a volta"
  No *a = ult->prox;
  for (int i = 0; i < 12; i++) { cout << a->valor << " "; a = a->prox; }
  cout << endl;
  libera(ult);
  return 0;
}
