/*
Exemplo 2. Codificacao de Huffman: codigo de tamanho variavel em que simbolos frequentes recebem codigos
curtos. E um codigo de prefixo (nenhum codigo e prefixo de outro), entao decodifica sem separadores.
Construcao (algoritmo guloso):
  1) cria uma folha para cada simbolo com peso = frequencia e coloca todas em um heap minimo;
  2) repete: tira as duas arvores de menor peso e junta como filhas de um novo no (peso = soma);
  3) a arvore final define os codigos: esquerda = 0, direita = 1.
O resultado minimiza o tamanho medio do codigo entre os codigos de prefixo para simbolos isolados.
*/
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct No {
  char simbolo;
  int peso;
  No *esq, *dir;
};

struct MaiorPeso {   // para o priority_queue virar heap minimo
  bool operator()(No *a, No *b) const { return a->peso > b->peso; }
};

No *constroiArvore(const map<char, int> &freq)
{
  priority_queue<No *, vector<No *>, MaiorPeso> heap;
  for (auto &f : freq) heap.push(new No{f.first, f.second, nullptr, nullptr});
  while (heap.size() > 1) {
    No *a = heap.top(); heap.pop();
    No *b = heap.top(); heap.pop();
    heap.push(new No{0, a->peso + b->peso, a, b});   // junta as duas menores
  }
  return heap.top();
}

void geraCodigos(No *r, const string &cod, map<char, string> &tabela)
{
  if (!r->esq) { tabela[r->simbolo] = cod.empty() ? "0" : cod; return; }   // folha
  geraCodigos(r->esq, cod + "0", tabela);
  geraCodigos(r->dir, cod + "1", tabela);
}

string decodifica(No *raiz, const string &bits)
{
  string s;
  No *a = raiz;
  for (char b : bits) {
    a = b == '0' ? a->esq : a->dir;
    if (!a->esq) { s += a->simbolo; a = raiz; }   // chegou numa folha: emite e volta para a raiz
  }
  return s;
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

int main()
{
  string texto = "abracadabra alakazam";
  map<char, int> freq;
  for (char c : texto) freq[c]++;

  No *raiz = constroiArvore(freq);
  map<char, string> tabela;
  geraCodigos(raiz, "", tabela);

  cout << "simbolo  freq  codigo" << endl;
  for (auto &t : tabela) cout << "  '" << t.first << "'    " << freq[t.first] << "    " << t.second << endl;

  string bits;
  for (char c : texto) bits += tabela[c];
  cout << "Codificado: " << bits << endl;
  cout << "Tamanho: " << bits.size() << " bits contra " << texto.size() * 8 << " bits em ASCII (razao "
       << (double)bits.size() / (texto.size() * 8) << ")" << endl;
  cout << "Decodificado: \"" << decodifica(raiz, bits) << "\"" << endl;
  libera(raiz);
  return 0;
}
