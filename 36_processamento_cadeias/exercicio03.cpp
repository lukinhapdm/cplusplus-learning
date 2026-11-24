/*
Exercicio 3. Pesquisa de frases com arquivo invertido: guardar, para cada palavra, o numero de ordem das
palavras no texto (1a palavra, 2a, ...). Uma frase "w1 w2 ... wk" ocorre na posicao p se w1 ocorre em p,
w2 em p+1, ..., wk em p+k-1. Comparar o numero de posicoes testadas com uma varredura do texto inteiro.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main()
{
  string texto = "a casa amarela fica na rua da casa azul e a casa azul fica na rua da escola "
                 "mas a escola azul fica longe da casa amarela";
  map<string, set<int>> indice;
  vector<string> palavras;
  stringstream ss(texto);
  string p;
  while (ss >> p) { indice[p].insert(palavras.size()); palavras.push_back(p); }

  for (string frase : {"casa azul", "fica na rua da", "casa amarela fica", "rua azul"}) {
    vector<string> f;
    stringstream sf(frase);
    while (sf >> p) f.push_back(p);

    int testes = 0;
    vector<int> resultado;
    for (int inicio : indice[f[0]]) {   // so as posicoes da primeira palavra sao candidatas
      bool ok = true;
      for (size_t k = 1; k < f.size() && ok; k++) {
        testes++;
        ok = indice[f[k]].count(inicio + k) > 0;   // a k-esima palavra esta na posicao certa?
      }
      if (ok) resultado.push_back(inicio);
    }
    cout << "\"" << frase << "\" nas palavras: ";
    for (int r : resultado) cout << r << " ";
    if (resultado.empty()) cout << "(nao ocorre)";
    cout << " [" << testes << " testes no indice; varredura testaria " << palavras.size() << " posicoes]" << endl;
  }
  return 0;
}
