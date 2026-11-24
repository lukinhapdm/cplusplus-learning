/*
Exercicio 1. Huffman baseado em palavras: em textos de linguagem natural, usar as PALAVRAS como simbolos
(e nao os caracteres) comprime muito mais, porque a distribuicao das palavras e bem desigual (lei de Zipf).
Calcular, para o mesmo texto, o total de bits do Huffman por caracteres e do Huffman por palavras
(separando palavras por espaco; o espaco fica implicito entre duas palavras).
Obs.: na pratica o vocabulario (tabela de codigos) tambem precisa ser guardado; aqui so contamos o texto.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

// so precisamos do tamanho total: soma dos pesos dos nos internos = soma de freq * tamanho do codigo
template <typename T>
long totalBits(const map<T, int> &freq)
{
  priority_queue<long, vector<long>, greater<long>> heap;
  for (auto &f : freq) heap.push(f.second);
  if (heap.size() == 1) return heap.top();   // um unico simbolo: 1 bit cada
  long total = 0;
  while (heap.size() > 1) {
    long a = heap.top(); heap.pop();
    long b = heap.top(); heap.pop();
    total += a + b;   // cada juncao acrescenta 1 bit a todos os simbolos abaixo dela
    heap.push(a + b);
  }
  return total;
}

int main()
{
  string texto;
  string frases[] = {"o rato roeu a roupa do rei de roma", "a rainha de roma ficou brava com o rato",
                     "o rei de roma mandou o gato pegar o rato", "o gato do rei de roma pegou o rato da roupa"};
  for (int rep = 0; rep < 5; rep++) for (const string &f : frases) texto += f + " ";

  map<char, int> freqC;
  for (char c : texto) freqC[c]++;
  map<string, int> freqP;
  stringstream ss(texto);
  string p;
  int palavras = 0;
  while (ss >> p) { freqP[p]++; palavras++; }

  long bitsC = totalBits(freqC), bitsP = totalBits(freqP);
  cout << "Texto: " << texto.size() << " caracteres, " << palavras << " palavras" << endl;
  cout << "ASCII:              " << texto.size() * 8 << " bits" << endl;
  cout << "Huffman caracteres: " << bitsC << " bits (" << freqC.size() << " simbolos, razao "
       << (double)bitsC / (texto.size() * 8) << ")" << endl;
  cout << "Huffman palavras:   " << bitsP << " bits (" << freqP.size() << " simbolos, razao "
       << (double)bitsP / (texto.size() * 8) << ")" << endl;
  return 0;
}
