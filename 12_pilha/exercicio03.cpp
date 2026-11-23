/*
Exercicio 3. Ler uma palavra e mostra-la invertida usando uma pilha dinamica de caracteres.
*/
#include <iostream>
using namespace std;

struct No { char c; No *prox; };

void empilha(No *&topo, char c) { No *n = new No; n->c = c; n->prox = topo; topo = n; }

char desempilha(No *&topo)
{
  No *aux = topo; char c = aux->c;
  topo = aux->prox; delete aux;
  return c;
}

int main()
{
  No *topo = nullptr;
  char s[100];
  cout << "Palavra: "; cin >> s;
  for (int i = 0; s[i] != '\0'; i++) empilha(topo, s[i]);
  cout << "Invertida: ";
  while (topo != nullptr) cout << desempilha(topo);   // sai do ultimo para o primeiro
  cout << endl;
  return 0;
}
