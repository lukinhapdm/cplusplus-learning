/*
Exercicio 3. Cobertura de vertices: conjunto C tal que toda aresta tem pelo menos uma ponta em C.
A minima e o complemento do maior conjunto independente (NP-dificil). Aproximacao 2: enquanto houver aresta
descoberta u-v, coloca u E v na cobertura. As arestas escolhidas formam um emparelhamento e qualquer cobertura
precisa de uma ponta de cada uma, entao o resultado tem no maximo 2 vezes o tamanho otimo.
Comparar a aproximacao com o otimo (forca bruta) em grafos aleatorios.
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main()
{
  srand(17);
  int n = 14;
  double piorRazao = 0;
  for (int t = 0; t < 8; t++) {
    vector<pair<int, int>> e;
    for (int u = 0; u < n; u++) for (int v = u + 1; v < n; v++) if (rand() % 4 == 0) e.push_back({u, v});

    // aproximacao: percorre as arestas; se nenhuma ponta esta coberta, pega as duas
    vector<bool> naC(n, false);
    int aprox = 0;
    for (auto &a : e) if (!naC[a.first] && !naC[a.second]) { naC[a.first] = naC[a.second] = true; aprox += 2; }

    // otimo por forca bruta
    int otimo = n;
    for (int S = 0; S < (1 << n); S++) {
      int tam = __builtin_popcount(S);
      if (tam >= otimo) continue;
      bool cobre = true;
      for (auto &a : e) if (!(S >> a.first & 1) && !(S >> a.second & 1)) { cobre = false; break; }
      if (cobre) otimo = tam;
    }
    double r = otimo ? (double)aprox / otimo : 1;
    piorRazao = max(piorRazao, r);
    cout << "Grafo " << t + 1 << " (" << e.size() << " arestas): otimo = " << otimo << ", aproximacao = " << aprox
         << " (razao " << r << ")" << endl;
  }
  cout << "Pior razao: " << piorRazao << " (garantia: <= 2)" << endl;
  return 0;
}
