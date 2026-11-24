/*
Exemplo 2. Mapas (dicionarios / arrays associativos): guardam pares (chave, valor), com chaves unicas.
Na STL:
- map: arvore vermelho-preto, percorre em ordem de chave, O(log n);
- unordered_map: tabela hash, O(1) em media, sem ordem;
- multimap: permite chaves repetidas.
Cuidado: m[chave] cria a chave (com valor padrao) se ela nao existir; para so consultar use find ou count.
*/
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>
using namespace std;

int main()
{
  // contagem de palavras com map: sai em ordem alfabetica
  string texto = "o tempo perguntou ao tempo quanto tempo o tempo tem";
  map<string, int> freq;
  stringstream ss(texto);
  string p;
  while (ss >> p) freq[p]++;   // se nao existe, cria com 0 e incrementa
  for (const auto &par : freq) cout << par.first << ": " << par.second << endl;

  // unordered_map: cadastro por codigo
  unordered_map<int, string> produtos = {{101, "caneta"}, {205, "caderno"}};
  produtos[310] = "mochila";
  produtos.insert({101, "lapis"});   // insert nao sobrescreve chave existente
  auto it = produtos.find(205);
  if (it != produtos.end()) cout << "\nProduto 205: " << it->second << endl;
  cout << "Produto 101: " << produtos[101] << endl;
  cout << "Existe 999? " << produtos.count(999) << endl;   // count nao cria a chave
  produtos.erase(310);
  cout << "Tamanho: " << produtos.size() << endl;

  // multimap: um aluno pode ter varias disciplinas
  multimap<string, string> matriculas = {{"ana", "calculo"}, {"bia", "fisica"}, {"ana", "algoritmos"}};
  auto faixa = matriculas.equal_range("ana");
  cout << "\nDisciplinas de ana: ";
  for (auto i = faixa.first; i != faixa.second; ++i) cout << i->second << " ";
  cout << endl;
  return 0;
}
