/*
Exercicio 4. Avaliar uma expressao posfixa (ex.: 5 3 + 2 *) com numeros de um digito usando pilha.
*/
#include <iostream>
using namespace std;

// Pilha dinamica: cada no aponta para o de baixo
struct No { int valor; No *prox; };
struct Pilha { No *topo; };

void inicia(Pilha &p) { p.topo = nullptr; }
bool vazia(Pilha &p) { return p.topo == nullptr; }

void empilha(Pilha &p, int x)
{
  No *n = new No;
  n->valor = x;
  n->prox = p.topo;   // novo no aponta para o antigo topo
  p.topo = n;
}

bool desempilha(Pilha &p, int &x)
{
  if (vazia(p)) return false;
  No *aux = p.topo;
  x = aux->valor;
  p.topo = aux->prox;
  delete aux;         // libera o no removido
  return true;
}

int main()
{
  Pilha p; inicia(p);
  char s[100];
  cout << "Expressao posfixa (ex.: 53+2*): "; cin.getline(s, 100);
  for (int i = 0; s[i] != '\0'; i++) {
    char c = s[i];
    if (c >= '0' && c <= '9') empilha(p, c - '0');   // numero: empilha
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b, a;
      desempilha(p, b); desempilha(p, a);           // operador: usa os dois do topo
      if (c == '+') empilha(p, a + b);
      else if (c == '-') empilha(p, a - b);
      else if (c == '*') empilha(p, a * b);
      else empilha(p, a / b);
    }
  }
  int r; desempilha(p, r);
  cout << "Resultado: " << r << endl;
  return 0;
}
