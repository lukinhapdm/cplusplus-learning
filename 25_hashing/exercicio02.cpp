/*
Exercicio 2. Contar a frequencia das palavras de um texto usando uma tabela hash com encadeamento
(chave string). Imprimir cada palavra com sua frequencia e o tamanho da maior lista.
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int M = 7;
struct No { string palavra; int freq; No *prox; };

int h(const string &s)
{
  unsigned long v = 0;
  for (char c : s) v = (v * 31 + (unsigned char)c) % M;
  return (int)v;
}

void conta(No *t[], const string &p)
{
  int i = h(p);
  for (No *a = t[i]; a; a = a->prox)
    if (a->palavra == p) { a->freq++; return; }   // ja existe: so incrementa
  t[i] = new No{p, 1, t[i]};                      // nova: insere no inicio da lista
}

int main()
{
  No *t[M] = {nullptr};
  string texto = "o rato roeu a roupa do rei de roma e o rei ficou bravo com o rato";
  stringstream ss(texto);
  string p;
  while (ss >> p) conta(t, p);

  int maior = 0;
  for (int i = 0; i < M; i++) {
    int tam = 0;
    cout << i << ": ";
    for (No *a = t[i]; a; a = a->prox) { cout << a->palavra << "(" << a->freq << ") "; tam++; }
    cout << endl;
    if (tam > maior) maior = tam;
  }
  cout << "Maior lista: " << maior << endl;

  for (int i = 0; i < M; i++)   // libera a memoria
    while (t[i]) { No *a = t[i]; t[i] = a->prox; delete a; }
  return 0;
}
