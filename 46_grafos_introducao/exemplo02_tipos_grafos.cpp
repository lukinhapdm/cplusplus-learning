/*
Exemplo 2. Tipos de grafos, verificados a partir da matriz de adjacencia (A[u][v] = numero de arestas u-v):
  - simples: sem lacos (A[u][u] = 0) e sem arestas multiplas (A[u][v] <= 1); senao e multigrafo;
  - completo K_n: todo par de vertices distintos e adjacente (m = n(n-1)/2);
  - k-regular: todos os vertices tem grau k;
  - bipartido: V se divide em X e Y sem arestas dentro de X nem dentro de Y
    (equivale a nao ter ciclo impar; testado colorindo com 2 cores por busca em largura);
  - complemento: mesmos vertices, arestas exatamente onde G nao tem.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

typedef vector<vector<int>> Matriz;

bool simples(const Matriz &A)
{
  for (size_t u = 0; u < A.size(); u++)
    for (size_t v = 0; v < A.size(); v++)
      if ((u == v && A[u][v]) || A[u][v] > 1) return false;
  return true;
}

int grau(const Matriz &A, int u) { int g = 0; for (int x : A[u]) g += x; return g; }

bool completo(const Matriz &A)
{
  for (size_t u = 0; u < A.size(); u++)
    for (size_t v = 0; v < A.size(); v++) if (u != v && A[u][v] != 1) return false;
  return simples(A);
}

int regular(const Matriz &A)   // devolve k, ou -1 se nao for regular
{
  int k = grau(A, 0);
  for (size_t u = 1; u < A.size(); u++) if (grau(A, u) != k) return -1;
  return k;
}

bool bipartido(const Matriz &A, vector<int> &cor)
{
  int n = A.size();
  cor.assign(n, -1);
  for (int s = 0; s < n; s++) {
    if (cor[s] != -1) continue;
    queue<int> f; f.push(s); cor[s] = 0;
    while (!f.empty()) {
      int u = f.front(); f.pop();
      for (int v = 0; v < n; v++)
        if (A[u][v]) {
          if (cor[v] == -1) { cor[v] = 1 - cor[u]; f.push(v); }
          else if (cor[v] == cor[u]) return false;   // vizinhos com a mesma cor: ciclo impar
        }
    }
  }
  return true;
}

Matriz complemento(const Matriz &A)
{
  int n = A.size();
  Matriz C(n, vector<int>(n, 0));
  for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) if (u != v) C[u][v] = !A[u][v];
  return C;
}

void analisa(const string &nome, const Matriz &A)
{
  vector<int> cor;
  int k = regular(A);
  cout << nome << ": " << (simples(A) ? "simples" : "multigrafo") << ", " << (completo(A) ? "completo" : "nao completo")
       << ", " << (k >= 0 ? to_string(k) + "-regular" : "nao regular") << ", ";
  if (bipartido(A, cor)) {
    cout << "bipartido X = {";
    for (size_t u = 0; u < A.size(); u++) if (cor[u] == 0) cout << " " << u;
    cout << " }";
  } else cout << "nao bipartido";
  cout << endl;
}

int main()
{
  Matriz K4 = {{0, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
  Matriz C6(6, vector<int>(6, 0));   // ciclo com 6 vertices
  for (int i = 0; i < 6; i++) C6[i][(i + 1) % 6] = C6[(i + 1) % 6][i] = 1;
  Matriz multi = {{1, 2, 0}, {2, 0, 1}, {0, 1, 0}};   // laco em 0 e aresta dupla 0-1
  analisa("K4", K4);
  analisa("C6", C6);
  analisa("Multigrafo", multi);
  analisa("Complemento de C6", complemento(C6));
  return 0;
}
