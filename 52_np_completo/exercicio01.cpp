/*
Exercicio 1. Reducao classica 3-SAT <=p CONJUNTO INDEPENDENTE (Karp). Para uma formula com m clausulas
de 3 literais:
  - cada clausula vira um triangulo (3 vertices, um por literal) -> o independente pega no maximo 1 por clausula;
  - liga por aresta todo par de vertices com literais contrarios (x e ~x) -> nao escolhe os dois.
A formula e satisfazivel se e somente se o grafo tem conjunto independente de tamanho m.
Conferir em formulas aleatorias, resolvendo 3-SAT e CONJUNTO INDEPENDENTE por forca bruta.
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef vector<vector<int>> CNF;

bool satisfazivel(const CNF &f, int n)
{
  for (int mask = 0; mask < (1 << n); mask++) {
    bool ok = true;
    for (auto &c : f) {
      bool sat = false;
      for (int l : c) if ((l > 0) == (bool)(mask >> (abs(l) - 1) & 1)) sat = true;
      if (!sat) { ok = false; break; }
    }
    if (ok) return true;
  }
  return false;
}

// grafo da reducao: vertice 3c + i = i-esimo literal da clausula c
vector<vector<bool>> constroiGrafo(const CNF &f)
{
  int V = 3 * f.size();
  vector<vector<bool>> g(V, vector<bool>(V, false));
  for (int a = 0; a < V; a++)
    for (int b = a + 1; b < V; b++) {
      bool mesmaClausula = a / 3 == b / 3;
      bool contrarios = f[a / 3][a % 3] == -f[b / 3][b % 3];
      if (mesmaClausula || contrarios) g[a][b] = g[b][a] = true;
    }
  return g;
}

// existe independente de tamanho m? backtracking escolhendo um vertice por clausula (ou nenhum nao basta)
bool independente(const vector<vector<bool>> &g, int clausula, int m, vector<int> &escolha)
{
  if (clausula == m) return true;
  for (int i = 0; i < 3; i++) {
    int v = 3 * clausula + i;
    bool ok = true;
    for (int u : escolha) if (g[u][v]) ok = false;
    if (!ok) continue;
    escolha.push_back(v);
    if (independente(g, clausula + 1, m, escolha)) return true;
    escolha.pop_back();
  }
  return false;
}

int main()
{
  srand(10);
  int n = 4, iguais = 0, total = 0, sats = 0;
  for (int t = 0; t < 200; t++) {
    int m = 8 + rand() % 12;
    CNF f(m, vector<int>(3));
    for (auto &c : f) for (int &l : c) l = (1 + rand() % n) * (rand() % 2 ? 1 : -1);
    bool a = satisfazivel(f, n);
    vector<int> esc;
    bool b = independente(constroiGrafo(f), 0, m, esc);   // independente de tamanho m usa 1 vertice por triangulo
    total++; iguais += a == b; sats += a;
  }
  cout << total << " formulas (" << sats << " satisfaziveis): reducao deu a mesma resposta em " << iguais << endl;
  return 0;
}
