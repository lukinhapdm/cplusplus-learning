/*
Exercicio 2. Ler um texto, contar a frequencia das palavras com unordered_map (ignorando maiusculas e
pontuacao) e mostrar as 3 mais frequentes. Para ordenar por frequencia, copiar os pares para um vector.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

string normaliza(const string &p)
{
  string r;
  for (char c : p) if (isalpha((unsigned char)c)) r += tolower(c);
  return r;
}

int main()
{
  string texto = "A fila anda. A pilha cresce, a pilha diminui; a fila nao para. "
                 "Quem chega primeiro na fila sai primeiro; quem chega por ultimo na pilha sai primeiro. "
                 "Fila, pilha, lista: tudo e estrutura de dados.";
  unordered_map<string, int> freq;
  stringstream ss(texto);
  string p;
  while (ss >> p) {
    p = normaliza(p);
    if (!p.empty()) freq[p]++;
  }

  vector<pair<string, int>> v(freq.begin(), freq.end());
  sort(v.begin(), v.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
    if (a.second != b.second) return a.second > b.second;   // mais frequente primeiro
    return a.first < b.first;                                // empate: ordem alfabetica
  });
  cout << "Palavras distintas: " << v.size() << endl;
  for (int i = 0; i < 3 && i < (int)v.size(); i++) cout << v[i].first << ": " << v[i].second << endl;
  return 0;
}
