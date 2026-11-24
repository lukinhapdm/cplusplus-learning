/*
Exemplo 1. Compressao de dados: representar a informacao com menos bits, explorando redundancia.
- Sem perda (texto, programas): descomprimir devolve exatamente o original. Ex.: RLE, Huffman, LZ.
- Com perda (imagem, audio, video): aceita diferencas pequenas em troca de mais compressao.
Razao de compressao = tamanho comprimido / tamanho original (quanto menor, melhor).
RLE (run-length encoding): troca cada sequencia de simbolos iguais por (quantidade, simbolo).
Funciona bem com longas repeticoes (imagens simples, fax); em texto comum pode ate aumentar o tamanho.
*/
#include <iostream>
#include <string>
using namespace std;

string comprimeRLE(const string &s)
{
  string r;
  for (size_t i = 0; i < s.size();) {
    size_t j = i;
    while (j < s.size() && s[j] == s[i] && j - i < 9) j++;   // corridas de no maximo 9 (um digito)
    r += char('0' + (j - i));
    r += s[i];
    i = j;
  }
  return r;
}

string descomprimeRLE(const string &r)
{
  string s;
  for (size_t i = 0; i + 1 < r.size(); i += 2) s += string(r[i] - '0', r[i + 1]);
  return s;
}

void testa(const string &s)
{
  string c = comprimeRLE(s);
  cout << "\"" << s << "\" -> \"" << c << "\"" << endl;
  cout << "  razao: " << (double)c.size() / s.size() << (descomprimeRLE(c) == s ? ", descompressao ok" : ", ERRO") << endl;
}

int main()
{
  testa("AAAAAAABBBCCCCCCCCCCCCDAAA");
  testa("WWWWWWWWWWWWBWWWWWWWWWWWWBBB");
  testa("texto comum");   // quase sem repeticoes: piora
  return 0;
}
