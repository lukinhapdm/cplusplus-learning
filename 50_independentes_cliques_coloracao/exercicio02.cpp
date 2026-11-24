/*
Exercicio 2. Calendario de provas: duas disciplinas que tem algum aluno em comum nao podem ter prova no
mesmo horario. Montar o grafo de conflitos (vertice = disciplina, aresta = aluno em comum), colorir
(cor = horario) e mostrar o menor numero de horarios (numero cromatico, por backtracking) e a grade.
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

vector<string> disc = {"Calculo", "Fisica", "Grafos", "PAA", "Banco de Dados", "Redes", "Ingles"};
vector<set<int>> adj;

bool colore(int u, int k, vector<int> &cor)
{
  if (u == (int)disc.size()) return true;
  for (int c = 0; c < k; c++) {
    bool ok = true;
    for (int v : adj[u]) if (cor[v] == c) ok = false;
    if (!ok) continue;
    cor[u] = c;
    if (colore(u + 1, k, cor)) return true;
    cor[u] = -1;
  }
  return false;
}

int main()
{
  vector<vector<int>> alunos = {   // disciplinas de cada aluno (indices em disc)
    {0, 1, 6}, {0, 2, 3}, {2, 3, 4}, {1, 5}, {4, 5, 6}, {3, 5}, {0, 4}};
  int n = disc.size();
  adj.assign(n, {});
  for (auto &a : alunos)
    for (int x : a) for (int y : a) if (x != y) adj[x].insert(y);   // todas as disciplinas do aluno conflitam

  vector<int> cor;
  int k = 1;
  while (true) {
    cor.assign(n, -1);
    if (colore(0, k, cor)) break;
    k++;
  }
  cout << "Minimo de horarios: " << k << endl;
  for (int c = 0; c < k; c++) {
    cout << "Horario " << c + 1 << ": ";
    for (int u = 0; u < n; u++) if (cor[u] == c) cout << disc[u] << "; ";
    cout << endl;
  }
  return 0;
}
