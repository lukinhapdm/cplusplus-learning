/*
Exercicio 1. Autocompletar: dado um prefixo, listar todas as palavras da trie que comecam com ele,
em ordem alfabetica, limitando a quantidade de sugestoes.
*/
#include <iostream>
#include <string>
using namespace std;

struct No { No *filho[26] = {nullptr}; bool fim = false; };

void insere(No *raiz, const string &s)
{
  for (char ch : s) {
    No *&f = raiz->filho[ch - 'a'];
    if (!f) f = new No;
    raiz = f;
  }
  raiz->fim = true;
}

// percorre a subarvore em profundidade; para quando atingir o limite
void coleta(No *n, string &atual, int &restantes)
{
  if (restantes == 0) return;
  if (n->fim) { cout << "  " << atual << endl; restantes--; }
  for (int c = 0; c < 26 && restantes > 0; c++)
    if (n->filho[c]) {
      atual.push_back('a' + c);
      coleta(n->filho[c], atual, restantes);
      atual.pop_back();
    }
}

void autocompleta(No *raiz, string prefixo, int limite)
{
  No *n = raiz;
  for (char ch : prefixo) {   // primeiro desce ate o fim do prefixo
    n = n->filho[ch - 'a'];
    if (!n) { cout << "  (nenhuma sugestao)" << endl; return; }
  }
  coleta(n, prefixo, limite);
}

void libera(No *n) { for (No *f : n->filho) if (f) libera(f); delete n; }

int main()
{
  No *raiz = new No;
  string dic[] = {"pato", "pata", "patio", "patins", "pateta", "paz", "pera", "pipoca", "patrao", "patriota"};
  for (const string &s : dic) insere(raiz, s);
  for (string p : {"pat", "pe", "pu"}) {
    cout << p << ":" << endl;
    autocompleta(raiz, p, 4);
  }
  libera(raiz);
  return 0;
}
