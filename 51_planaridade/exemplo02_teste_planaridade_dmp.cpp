/*
Exemplo 2. Teste de planaridade de Demoucron, Malgrange e Pertuiset (DMP) para grafos 2-conexos
(para um grafo qualquer, basta testar cada componente biconexa).
Constroi um desenho plano H aos poucos:
  1) H = um ciclo qualquer de G, que tem 2 faces (dentro e fora).
  2) Fragmentos de G em relacao a H: (a) uma aresta fora de H com as duas pontas em H, ou
     (b) uma componente de G - V(H) junto com as arestas que a ligam a H. Os vertices de H tocados
     pelo fragmento sao os contatos. Uma face e admissivel para o fragmento se contem todos os contatos.
  3) Se algum fragmento nao tem face admissivel: G nao e planar. Senao escolhe um fragmento com uma unica
     face admissivel (ou qualquer um, se todos tem 2 ou mais), pega um caminho dentro dele ligando dois
     contatos e o desenha dentro da face, que se divide em duas.
  4) Repete ate nao sobrar fragmento: G e planar e as faces descrevem um desenho plano.
Cada face e guardada como a lista ciclica dos vertices da sua borda.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

int n;
vector<vector<int>> G;      // matriz de adjacencia
vector<bool> emH;
vector<vector<bool>> arestaH;
vector<vector<int>> faces;

struct Fragmento { vector<int> contatos, interior; int u = -1, v = -1; };

bool achaCiclo(int u, int pai, vector<int> &pilha, vector<int> &estado, vector<int> &ciclo)
{
  estado[u] = 1; pilha.push_back(u);
  for (int v = 0; v < n; v++) {
    if (!G[u][v] || v == pai) continue;
    if (estado[v] == 1) {   // aresta de retorno: o ciclo e o trecho da pilha de v ate u
      ciclo.assign(find(pilha.begin(), pilha.end(), v), pilha.end());
      return true;
    }
    if (estado[v] == 0 && achaCiclo(v, u, pilha, estado, ciclo)) return true;
  }
  pilha.pop_back(); estado[u] = 2;
  return false;
}

vector<Fragmento> fragmentos()
{
  vector<Fragmento> fr;
  for (int u = 0; u < n; u++)   // tipo (a): aresta solta entre vertices de H
    for (int v = u + 1; v < n; v++)
      if (G[u][v] && emH[u] && emH[v] && !arestaH[u][v]) { Fragmento f; f.u = u; f.v = v; f.contatos = {u, v}; fr.push_back(f); }
  vector<bool> vis(n, false);
  for (int s = 0; s < n; s++) {  // tipo (b): componentes fora de H
    if (emH[s] || vis[s]) continue;
    Fragmento f;
    vector<bool> contato(n, false);
    queue<int> q; q.push(s); vis[s] = true;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      f.interior.push_back(x);
      for (int y = 0; y < n; y++) {
        if (!G[x][y]) continue;
        if (emH[y]) contato[y] = true;
        else if (!vis[y]) { vis[y] = true; q.push(y); }
      }
    }
    for (int y = 0; y < n; y++) if (contato[y]) f.contatos.push_back(y);
    fr.push_back(f);
  }
  return fr;
}

bool admissivel(const vector<int> &face, const Fragmento &f)
{
  for (int c : f.contatos) if (find(face.begin(), face.end(), c) == face.end()) return false;
  return true;
}

// caminho dentro do fragmento ligando dois contatos diferentes
vector<int> caminho(const Fragmento &f)
{
  if (f.u >= 0) return {f.u, f.v};
  vector<bool> dentro(n, false);
  for (int x : f.interior) dentro[x] = true;
  int a = f.contatos[0], x0 = -1;
  for (int x : f.interior) if (G[x][a]) { x0 = x; break; }
  vector<int> pai(n, -1);
  vector<bool> vis(n, false);
  queue<int> q; q.push(x0); vis[x0] = true;
  while (!q.empty()) {
    int x = q.front(); q.pop();
    for (int b : f.contatos)
      if (b != a && G[x][b]) {   // chegou perto de outro contato: monta a, x0, ..., x, b
        vector<int> c = {b};
        for (int y = x; y != -1; y = pai[y]) c.push_back(y);
        c.push_back(a);
        reverse(c.begin(), c.end());
        return c;
      }
    for (int y = 0; y < n; y++) if (dentro[y] && G[x][y] && !vis[y]) { vis[y] = true; pai[y] = x; q.push(y); }
  }
  return {};
}

// desenha o caminho p (a ... b) dentro da face k, dividindo-a em duas
void divideFace(int k, const vector<int> &p)
{
  vector<int> F = faces[k];
  int m = F.size(), i = find(F.begin(), F.end(), p.front()) - F.begin(), j = find(F.begin(), F.end(), p.back()) - F.begin();
  vector<int> f1, f2;
  for (int t = i;; t = (t + 1) % m) { f1.push_back(F[t]); if (t == j) break; }   // a ... b pela borda
  for (int t = p.size() - 2; t >= 1; t--) f1.push_back(p[t]);                     // volta b -> a pelo caminho
  for (int t = j;; t = (t + 1) % m) { f2.push_back(F[t]); if (t == i) break; }   // b ... a pela borda
  for (size_t t = 1; t + 1 < p.size(); t++) f2.push_back(p[t]);                  // a -> b pelo caminho
  faces[k] = f1;
  faces.push_back(f2);
  for (size_t t = 0; t + 1 < p.size(); t++) { emH[p[t]] = emH[p[t + 1]] = true; arestaH[p[t]][p[t + 1]] = arestaH[p[t + 1]][p[t]] = true; }
}

bool planar()
{
  emH.assign(n, false); arestaH.assign(n, vector<bool>(n, false)); faces.clear();
  vector<int> pilha, estado(n, 0), ciclo;
  achaCiclo(0, -1, pilha, estado, ciclo);
  for (size_t t = 0; t < ciclo.size(); t++) {
    int u = ciclo[t], v = ciclo[(t + 1) % ciclo.size()];
    emH[u] = true; arestaH[u][v] = arestaH[v][u] = true;
  }
  faces = {ciclo, ciclo};   // interna e externa
  while (true) {
    vector<Fragmento> fr = fragmentos();
    if (fr.empty()) return true;
    int escolhido = -1, face = -1;
    for (size_t k = 0; k < fr.size(); k++) {
      int qtd = 0, ultima = -1;
      for (size_t f = 0; f < faces.size(); f++) if (admissivel(faces[f], fr[k])) { qtd++; ultima = f; }
      if (qtd == 0) return false;                         // nao cabe em face nenhuma
      if (qtd == 1 || escolhido < 0) { escolhido = k; face = ultima; if (qtd == 1) break; }
    }
    divideFace(face, caminho(fr[escolhido]));
  }
}

void testa(const string &nome, int v, const vector<pair<int, int>> &e)
{
  n = v;
  G.assign(n, vector<int>(n, 0));
  for (auto &a : e) G[a.first][a.second] = G[a.second][a.first] = 1;
  cout << nome << ": ";
  if (!planar()) { cout << "NAO planar" << endl; return; }
  cout << "planar, " << faces.size() << " faces (Euler: " << (int)e.size() - n + 2 << "):";
  for (auto &f : faces) { cout << " ["; for (size_t i = 0; i < f.size(); i++) cout << (i ? " " : "") << f[i]; cout << "]"; }
  cout << endl;
}

int main()
{
  vector<pair<int, int>> k4 = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
  vector<pair<int, int>> cubo = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
  vector<pair<int, int>> k5, k33;
  for (int u = 0; u < 5; u++) for (int v = u + 1; v < 5; v++) k5.push_back({u, v});
  for (int u = 0; u < 3; u++) for (int v = 3; v < 6; v++) k33.push_back({u, v});
  testa("K4", 4, k4);
  testa("Cubo", 8, cubo);
  testa("K5", 5, k5);
  testa("K3,3", 6, k33);
  return 0;
}
