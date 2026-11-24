/*
Exemplo 2. Arquivo invertido (indice invertido): o texto e pre-processado em duas partes
  - vocabulario: conjunto das palavras distintas do texto;
  - ocorrencias: para cada palavra, a lista das posicoes em que ela aparece.
A pesquisa procura a palavra no vocabulario (arvore, hash, vetor ordenado...) e devolve a lista de
posicoes, sem varrer o texto. Pela lei de Heaps o vocabulario cresce bem mais devagar que o texto
(aprox. n^beta, beta entre 0.4 e 0.6), entao normalmente cabe em memoria.
Aqui a posicao e o deslocamento (indice do caractere) do inicio da palavra no texto.
*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

typedef map<string, vector<int>> ArquivoInvertido;   // vocabulario -> lista de ocorrencias

ArquivoInvertido constroi(const string &texto)
{
  ArquivoInvertido indice;
  int i = 0, n = texto.size();
  while (i < n) {
    while (i < n && !isalpha((unsigned char)texto[i])) i++;   // pula separadores
    int inicio = i;
    string palavra;
    while (i < n && isalpha((unsigned char)texto[i])) palavra += tolower(texto[i++]);
    if (!palavra.empty()) indice[palavra].push_back(inicio);
  }
  return indice;
}

void pesquisa(const ArquivoInvertido &indice, const string &texto, const string &palavra)
{
  auto it = indice.find(palavra);
  cout << "\"" << palavra << "\": ";
  if (it == indice.end()) { cout << "nao ocorre" << endl; return; }
  for (int pos : it->second) cout << pos << " ";
  cout << "-> contexto: \"" << texto.substr(it->second[0], 25) << "...\"" << endl;
}

int main()
{
  string texto = "Texto tem palavras. Palavras tem letras. O indice guarda palavras e posicoes; "
                 "o texto nao precisa ser lido de novo para cada pesquisa.";
  ArquivoInvertido indice = constroi(texto);

  cout << "Vocabulario (" << indice.size() << " palavras):" << endl;
  for (const auto &e : indice) {
    cout << "  " << e.first << ":";
    for (int p : e.second) cout << " " << p;
    cout << endl;
  }
  pesquisa(indice, texto, "palavras");
  pesquisa(indice, texto, "pesquisa");
  pesquisa(indice, texto, "arvore");
  return 0;
}
