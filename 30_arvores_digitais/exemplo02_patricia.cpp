/*
Exemplo 2. Arvore Patricia (Practical Algorithm To Retrieve Information Coded In Alphanumeric).
Trie binaria compactada: os nos internos guardam so o indice do bit a ser testado (0 -> esq, 1 -> dir)
e as chaves ficam nos nos externos (folhas). Caminhos sem bifurcacao sao eliminados, entao com n chaves
ha exatamente n - 1 nos internos. Os indices crescem ao descer na arvore.
Insercao: desce ate uma folha, acha o primeiro bit i em que a chave nova difere da chave da folha e
cria um no interno com indice i na posicao certa do caminho.
Aqui as chaves tem D = 8 bits e os bits sao numerados de 1 (mais a esquerda) a D.
*/
#include <iostream>
using namespace std;

const int D = 8;

struct No {
  bool externo;
  int indice;      // no interno: bit testado
  int chave;       // no externo: chave
  No *esq, *dir;
};

int bit(int i, int k) { return (k >> (D - i)) & 1; }

No *criaExterno(int k) { return new No{true, 0, k, nullptr, nullptr}; }
No *criaInterno(int i, No *esq, No *dir) { return new No{false, i, 0, esq, dir}; }

bool busca(No *t, int k)
{
  if (!t) return false;
  while (!t->externo) t = bit(t->indice, k) ? t->dir : t->esq;
  return t->chave == k;   // so na folha compara a chave inteira
}

// insere k abaixo de t, criando no interno com indice i
No *insereEntre(int k, No *t, int i)
{
  if (t->externo || i < t->indice) {   // achou o lugar: antes de um no com indice maior
    No *p = criaExterno(k);
    return bit(i, k) ? criaInterno(i, t, p) : criaInterno(i, p, t);
  }
  if (bit(t->indice, k)) t->dir = insereEntre(k, t->dir, i);
  else t->esq = insereEntre(k, t->esq, i);
  return t;
}

No *insere(No *t, int k)
{
  if (!t) return criaExterno(k);
  No *p = t;
  while (!p->externo) p = bit(p->indice, k) ? p->dir : p->esq;
  int i = 1;
  while (i <= D && bit(i, k) == bit(i, p->chave)) i++;   // primeiro bit diferente
  if (i > D) { cout << k << " ja esta na arvore" << endl; return t; }
  return insereEntre(k, t, i);
}

void binario(int k) { for (int i = 1; i <= D; i++) cout << bit(i, k); }

void desenha(No *t, int nivel = 0)
{
  if (!t) return;
  if (!t->externo) desenha(t->dir, nivel + 1);
  for (int i = 0; i < nivel; i++) cout << "      ";
  if (t->externo) { cout << t->chave << " ("; binario(t->chave); cout << ")" << endl; }
  else cout << "[" << t->indice << "]" << endl;
  if (!t->externo) desenha(t->esq, nivel + 1);
}

void libera(No *t) { if (t) { libera(t->esq); libera(t->dir); delete t; } }

int main()
{
  No *t = nullptr;
  int chaves[] = {18, 72, 9, 150, 19, 76, 9};   // 18 = 00010010 e 19 = 00010011 so diferem no bit 8
  for (int k : chaves) t = insere(t, k);
  desenha(t);
  cout << "busca(76) = " << busca(t, 76) << ", busca(77) = " << busca(t, 77) << endl;
  libera(t);
  return 0;
}
