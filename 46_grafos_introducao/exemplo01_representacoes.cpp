/*
Exemplo 1. Grafo G = (V, E): conjunto de vertices V e de arestas E (pares de vertices).
n = |V|, m = |E|. Representacoes:
  - matriz de adjacencia: A[u][v] = 1 se existe aresta u-v. Espaco O(n^2); teste de aresta O(1).
  - lista de adjacencia: para cada vertice, a lista de vizinhos. Espaco O(n + m); boa para grafos esparsos.
Grau de um vertice = numero de arestas incidentes. Lema do aperto de maos: soma dos graus = 2m
(cada aresta conta para as duas pontas), logo o numero de vertices de grau impar e par.
Em grafo direcionado (digrafo) ha grau de entrada e de saida, e soma das entradas = soma das saidas = m.
*/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n = 5;
  int arestas[][2] = {{0, 1}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}};
  int m = 7;

  vector<vector<int>> matriz(n, vector<int>(n, 0));
  vector<vector<int>> lista(n);
  for (int i = 0; i < m; i++) {
    int u = arestas[i][0], v = arestas[i][1];
    matriz[u][v] = matriz[v][u] = 1;   // nao direcionado: simetrica
    lista[u].push_back(v);
    lista[v].push_back(u);
  }

  cout << "Matriz de adjacencia:" << endl;
  for (int u = 0; u < n; u++) {
    cout << "  ";
    for (int v = 0; v < n; v++) cout << matriz[u][v] << " ";
    cout << endl;
  }
  cout << "Lista de adjacencia e graus:" << endl;
  int somaGraus = 0;
  for (int u = 0; u < n; u++) {
    cout << "  " << u << ": ";
    for (int v : lista[u]) cout << v << " ";
    cout << "(grau " << lista[u].size() << ")" << endl;
    somaGraus += lista[u].size();
  }
  cout << "Soma dos graus = " << somaGraus << " = 2m = " << 2 * m << endl;

  // digrafo: arcos u -> v
  int arcos[][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};   // (3,3) e um laco
  vector<int> entrada(4, 0), saida(4, 0);
  for (auto &a : arcos) { saida[a[0]]++; entrada[a[1]]++; }
  cout << "\nDigrafo:" << endl;
  for (int u = 0; u < 4; u++) cout << "  " << u << ": entrada " << entrada[u] << ", saida " << saida[u] << endl;
  return 0;
}
