/*
Exercicio 2. Grade curricular: disciplinas com pre-requisitos formam um DAG. Usando a ordenacao topologica,
calcular o semestre minimo de cada disciplina (1 + maior semestre entre os seus pre-requisitos, o que e um
caminho mais longo no DAG) e o numero minimo de semestres para concluir o curso.
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

int main()
{
  vector<string> nome = {"Logica", "AED I", "AED II", "Calculo I", "Calculo II", "Discreta",
                         "PAA", "Grafos", "Compiladores", "Numerico"};
  map<string, int> id;
  for (size_t i = 0; i < nome.size(); i++) id[nome[i]] = i;
  vector<pair<string, string>> pre = {   // (pre-requisito, disciplina)
    {"Logica", "AED I"}, {"AED I", "AED II"}, {"Calculo I", "Calculo II"}, {"AED II", "PAA"},
    {"Discreta", "PAA"}, {"Discreta", "Grafos"}, {"AED II", "Grafos"}, {"PAA", "Compiladores"},
    {"Calculo II", "Numerico"}, {"Logica", "Numerico"}};

  int n = nome.size();
  vector<vector<int>> adj(n);
  vector<int> entrada(n, 0), semestre(n, 1);
  for (auto &p : pre) { adj[id[p.first]].push_back(id[p.second]); entrada[id[p.second]]++; }

  queue<int> livres;
  for (int u = 0; u < n; u++) if (!entrada[u]) livres.push(u);
  int processadas = 0;
  while (!livres.empty()) {   // Kahn: quando u sai, todos os seus pre-requisitos ja foram processados
    int u = livres.front(); livres.pop(); processadas++;
    for (int v : adj[u]) {
      semestre[v] = max(semestre[v], semestre[u] + 1);
      if (--entrada[v] == 0) livres.push(v);
    }
  }
  if (processadas < n) { cout << "Pre-requisitos circulares!" << endl; return 0; }

  int total = 0;
  for (int u = 0; u < n; u++) total = max(total, semestre[u]);
  for (int s = 1; s <= total; s++) {
    cout << s << "o semestre: ";
    for (int u = 0; u < n; u++) if (semestre[u] == s) cout << nome[u] << "; ";
    cout << endl;
  }
  cout << "Minimo de semestres: " << total << endl;
  return 0;
}
