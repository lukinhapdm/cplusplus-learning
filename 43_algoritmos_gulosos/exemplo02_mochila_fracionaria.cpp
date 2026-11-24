/*
Exemplo 2. Mochila fracionaria: itens com peso e valor; a mochila aguenta W e podemos levar FRACOES de itens.
Guloso otimo: ordenar pela razao valor/peso e encher a mochila com os itens de maior razao,
pegando so uma fracao do ultimo que nao couber inteiro. Custo O(n log n).
Na mochila 0/1 (item inteiro ou nada) o mesmo guloso NAO e otimo: ver o contraexemplo abaixo
(a versao 0/1 e resolvida com programacao dinamica, na pasta 45).
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Item { string nome; double peso, valor; };

double fracionaria(vector<Item> itens, double W, bool inteiros)
{
  sort(itens.begin(), itens.end(), [](const Item &a, const Item &b) { return a.valor / a.peso > b.valor / b.peso; });
  double total = 0;
  for (const Item &it : itens) {
    if (W <= 0) break;
    if (it.peso <= W) {
      W -= it.peso; total += it.valor;
      cout << "  leva " << it.nome << " inteiro" << endl;
    } else if (!inteiros) {
      double f = W / it.peso;   // so cabe uma parte
      total += f * it.valor;
      cout << "  leva " << f * 100 << "% de " << it.nome << endl;
      W = 0;
    }
  }
  return total;
}

int main()
{
  vector<Item> itens = {{"ouro", 10, 60}, {"prata", 20, 100}, {"bronze", 30, 120}};
  cout << "Fracionaria, W = 50:" << endl;
  double v = fracionaria(itens, 50, false);
  cout << "  valor total = " << v << endl;
  cout << "Mesmo guloso na mochila 0/1, W = 50:" << endl;
  v = fracionaria(itens, 50, true);
  cout << "  valor total = " << v << " (o otimo e 220: prata + bronze)" << endl;
  return 0;
}
