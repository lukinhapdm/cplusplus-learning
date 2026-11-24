/*
Exemplo 1. Grafo planar: pode ser desenhado no plano sem cruzamento de arestas. Um desenho assim divide o
plano em faces (regioes), contando a face externa ilimitada.
Formula de Euler (grafo planar conexo): v - e + f = 2.
Consequencias (grafo simples planar conexo com v >= 3):
  - toda face e limitada por pelo menos 3 arestas e cada aresta borda no maximo 2 faces: 3f <= 2e,
    logo e <= 3v - 6;
  - sem triangulos (ex.: bipartido), cada face tem pelo menos 4 arestas: e <= 2v - 4;
  - em geral, com cintura (menor ciclo) g: e <= g (v - 2) / (g - 2).
Sao condicoes NECESSARIAS: se falharem o grafo nao e planar; se valerem, nada se conclui.
Kuratowski: G e planar se e somente se nao contem subdivisao de K5 nem de K3,3.
*/
#include <iostream>
#include <string>
using namespace std;

struct Info { string nome; int v, e, cintura; bool planar; };

int main()
{
  Info g[] = {
    {"K4", 4, 6, 3, true}, {"Cubo", 8, 12, 4, true}, {"Octaedro", 6, 12, 3, true}, {"Dodecaedro", 20, 30, 5, true},
    {"K5", 5, 10, 3, false}, {"K3,3", 6, 9, 4, false}, {"Petersen", 10, 15, 5, false},
    {"K3,3 + cauda de 3", 9, 12, 4, false}};   // passa nos dois testes e mesmo assim nao e planar

  for (const Info &x : g) {
    cout << x.nome << " (v = " << x.v << ", e = " << x.e << ", cintura " << x.cintura << "): ";
    bool passa3 = x.e <= 3 * x.v - 6;
    bool passaG = x.e * (x.cintura - 2) <= x.cintura * (x.v - 2);   // e <= g(v-2)/(g-2) sem divisao
    cout << "e <= 3v-6 " << (passa3 ? "ok" : "FALHA") << "; com cintura " << (passaG ? "ok" : "FALHA");
    if (!passa3 || !passaG) cout << " -> nao planar";
    else if (x.planar) cout << " -> planar, faces f = e - v + 2 = " << x.e - x.v + 2;
    else cout << " -> teste inconclusivo (na verdade nao e planar)";
    cout << endl;
  }
  return 0;
}
