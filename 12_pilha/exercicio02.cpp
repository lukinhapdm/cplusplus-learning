/*
Exercicio 2. Verificar se os parenteses, colchetes e chaves de uma expressao estao balanceados usando pilha.
*/
#include <iostream>
using namespace std;

const int MAX = 200;
struct Pilha { char dados[MAX]; int topo; };

void inicia(Pilha &p) { p.topo = 0; }
bool vazia(Pilha &p) { return p.topo == 0; }
void empilha(Pilha &p, char c) { p.dados[p.topo++] = c; }
char desempilha(Pilha &p) { return p.dados[--p.topo]; }

bool balanceada(const char s[])
{
  Pilha p; inicia(p);
  for (int i = 0; s[i] != '\0'; i++) {
    char c = s[i];
    if (c == '(' || c == '[' || c == '{') empilha(p, c);   // abre: guarda
    else if (c == ')' || c == ']' || c == '}') {
      if (vazia(p)) return false;                          // fechou sem abrir
      char a = desempilha(p);
      // o que fecha precisa combinar com o ultimo que abriu
      if ((c == ')' && a != '(') || (c == ']' && a != '[') || (c == '}' && a != '{')) return false;
    }
  }
  return vazia(p);   // sobrou algo aberto = desbalanceada
}

int main()
{
  char s[MAX];
  cout << "Expressao: "; cin.getline(s, MAX);
  cout << (balanceada(s) ? "Balanceada" : "Nao balanceada") << endl;
  return 0;
}
