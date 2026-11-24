/*
Exercicio 3. Gravar de verdade um arquivo comprimido com Huffman: empacotar os bits em bytes (8 por byte)
e gravar no arquivo o cabecalho (tabela de frequencias e quantidade de simbolos) seguido dos dados.
Depois ler o arquivo, reconstruir a arvore pelas frequencias e descomprimir. Comparar os tamanhos.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

struct No { int simbolo, peso; No *esq, *dir; };
struct MaiorPeso { bool operator()(No *a, No *b) const { return a->peso > b->peso; } };

No *constroi(const int freq[256])
{
  priority_queue<No *, vector<No *>, MaiorPeso> h;
  for (int c = 0; c < 256; c++) if (freq[c]) h.push(new No{c, freq[c], nullptr, nullptr});
  if (h.size() == 1) h.push(new No{-1, 0, nullptr, nullptr});   // garante pelo menos um no interno
  while (h.size() > 1) {
    No *a = h.top(); h.pop();
    No *b = h.top(); h.pop();
    h.push(new No{-1, a->peso + b->peso, a, b});
  }
  return h.top();
}

void codigos(No *r, string cod, string tab[256])
{
  if (!r->esq) { if (r->simbolo >= 0) tab[r->simbolo] = cod; return; }
  codigos(r->esq, cod + "0", tab);
  codigos(r->dir, cod + "1", tab);
}

void libera(No *r) { if (r) { libera(r->esq); libera(r->dir); delete r; } }

void comprime(const string &texto, const char *arq)
{
  int freq[256] = {0};
  for (unsigned char c : texto) freq[c]++;
  No *raiz = constroi(freq);
  string tab[256];
  codigos(raiz, "", tab);

  ofstream f(arq, ios::binary);
  int n = texto.size();
  f.write((char *)freq, sizeof(freq));   // cabecalho: 256 inteiros
  f.write((char *)&n, sizeof(n));
  unsigned char byte = 0;
  int usados = 0;
  for (unsigned char c : texto)
    for (char b : tab[c]) {
      byte = (byte << 1) | (b == '1');   // acrescenta 1 bit
      if (++usados == 8) { f.put(byte); byte = 0; usados = 0; }
    }
  if (usados > 0) f.put(byte << (8 - usados));   // completa o ultimo byte com zeros
  libera(raiz);
}

string descomprime(const char *arq)
{
  ifstream f(arq, ios::binary);
  int freq[256], n;
  f.read((char *)freq, sizeof(freq));
  f.read((char *)&n, sizeof(n));
  No *raiz = constroi(freq), *a = raiz;   // mesma arvore, pois as frequencias sao as mesmas
  string s;
  char byte;
  while ((int)s.size() < n && f.get(byte))
    for (int i = 7; i >= 0 && (int)s.size() < n; i--) {
      a = ((byte >> i) & 1) ? a->dir : a->esq;
      if (!a->esq) { s += (char)a->simbolo; a = raiz; }
    }
  libera(raiz);
  return s;
}

int main()
{
  string texto;
  for (int i = 0; i < 200; i++) texto += "compressao de dados com codigo de huffman. ";
  { ofstream o("original.txt"); o << texto; }

  comprime(texto, "comprimido.huf");
  string volta = descomprime("comprimido.huf");

  ifstream a("original.txt", ios::binary | ios::ate), b("comprimido.huf", ios::binary | ios::ate);
  long tamA = a.tellg(), tamB = b.tellg();
  cout << "Original:   " << tamA << " bytes" << endl;
  cout << "Comprimido: " << tamB << " bytes (cabecalho de " << 256 * sizeof(int) + sizeof(int) << " bytes)" << endl;
  cout << "Razao: " << (double)tamB / tamA << endl;
  cout << "Descompressao " << (volta == texto ? "correta" : "INCORRETA") << endl;
  return 0;
}
