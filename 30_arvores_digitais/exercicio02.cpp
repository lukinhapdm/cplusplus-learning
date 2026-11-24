/*
Exercicio 2. Guardar em cada no da trie quantas palavras passam por ele, para responder em O(m)
"quantas palavras comecam com o prefixo p?". Ler um texto e tambem contar a frequencia de cada palavra.
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct No {
  No *filho[26] = {nullptr};
  int passam = 0;   // palavras (com repeticao) que tem este prefixo
  int termina = 0;  // quantas vezes a palavra exata foi inserida
};

void insere(No *raiz, const string &s)
{
  No *n = raiz;
  n->passam++;
  for (char ch : s) {
    No *&f = n->filho[ch - 'a'];
    if (!f) f = new No;
    n = f;
    n->passam++;
  }
  n->termina++;
}

No *desce(No *n, const string &p)
{
  for (char ch : p) { n = n->filho[ch - 'a']; if (!n) return nullptr; }
  return n;
}

int comPrefixo(No *raiz, const string &p) { No *n = desce(raiz, p); return n ? n->passam : 0; }
int frequencia(No *raiz, const string &s) { No *n = desce(raiz, s); return n ? n->termina : 0; }

void libera(No *n) { for (No *f : n->filho) if (f) libera(f); delete n; }

int main()
{
  No *raiz = new No;
  stringstream texto("a aranha arranha a jarra a jarra arranha a aranha nem a aranha arranha a jarra nem a jarra arranha a aranha");
  string p;
  while (texto >> p) insere(raiz, p);
  cout << "Total de palavras: " << raiz->passam << endl;
  for (string q : {"a", "ar", "ara", "arr", "j", "n"}) cout << "Comecam com '" << q << "': " << comPrefixo(raiz, q) << endl;
  for (string q : {"aranha", "arranha", "jarra", "rato"}) cout << "Frequencia de '" << q << "': " << frequencia(raiz, q) << endl;
  libera(raiz);
  return 0;
}
