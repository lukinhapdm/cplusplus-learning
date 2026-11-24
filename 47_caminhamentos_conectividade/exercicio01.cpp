/*
Exercicio 1. Ciclo hamiltoniano: passa por TODOS os vertices exatamente uma vez e volta ao inicio.
Diferente do euleriano, nao ha condicao simples de verificar (e um problema NP-completo).
Resolver por backtracking: estende o caminho com um vizinho ainda nao visitado e volta quando travar.
Testar no dodecaedro (hamiltoniano, jogo de Hamilton) e no grafo de Petersen (nao hamiltoniano).
*/
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> caminho;
vector<bool> usado;
long long nos;

bool estende(int n)
{
  nos++;
  int u = caminho.back();
  if ((int)caminho.size() == n) {
    for (int v : adj[u]) if (v == caminho[0]) return true;   // fecha o ciclo?
    return false;
  }
  for (int v : adj[u])
    if (!usado[v]) {
      usado[v] = true; caminho.push_back(v);
      if (estende(n)) return true;
      usado[v] = false; caminho.pop_back();   // backtrack
    }
  return false;
}

void testa(const char *nome, int n, const vector<pair<int, int>> &arestas)
{
  adj.assign(n, {});
  for (auto &a : arestas) { adj[a.first].push_back(a.second); adj[a.second].push_back(a.first); }
  usado.assign(n, false); caminho = {0}; usado[0] = true; nos = 0;
  cout << nome << ": ";
  if (estende(n)) { for (int v : caminho) cout << v << "-"; cout << "0"; }
  else cout << "nao hamiltoniano";
  cout << " (" << nos << " nos na busca)" << endl;
}

int main()
{
  vector<pair<int, int>> petersen;
  for (int i = 0; i < 5; i++) {
    petersen.push_back({i, (i + 1) % 5});            // ciclo externo
    petersen.push_back({i, i + 5});                  // raios
    petersen.push_back({i + 5, (i + 2) % 5 + 5});    // estrela interna
  }
  testa("Petersen", 10, petersen);

  vector<pair<int, int>> dodecaedro = {
    {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9},
    {5, 10}, {10, 6}, {6, 11}, {11, 7}, {7, 12}, {12, 8}, {8, 13}, {13, 9}, {9, 14}, {14, 5},
    {10, 15}, {11, 16}, {12, 17}, {13, 18}, {14, 19}, {15, 16}, {16, 17}, {17, 18}, {18, 19}, {19, 15}};
  testa("Dodecaedro", 20, dodecaedro);
  return 0;
}
