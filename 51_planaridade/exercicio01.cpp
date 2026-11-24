/*
Exercicio 1. Teorema de Kuratowski na pratica, usando o teste DMP:
  (a) subdivisoes de K5 e K3,3 (trocar arestas por caminhos) continuam NAO planares;
  (b) tirando qualquer aresta de K5 ou de K3,3 o grafo vira planar (sao minimais nao planares);
  (c) o grafo de Petersen nao e planar (contem uma subdivisao de K3,3);
  (d) familias planares: rodas, prismas e K2,n.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

// ---------- teste de planaridade DMP (mesmo codigo do exemplo 2) ----------
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

// ---------------------------------------------------------------------------

typedef vector<pair<int, int>> Arestas;

bool testa(int v, const Arestas &e)
{
  n = v;
  G.assign(n, vector<int>(n, 0));
  for (auto &a : e) G[a.first][a.second] = G[a.second][a.first] = 1;
  return planar();
}

// troca cada aresta u-v por um caminho u-x-v com um vertice novo x
Arestas subdivide(int &v, const Arestas &e)
{
  Arestas r;
  for (auto &a : e) { r.push_back({a.first, v}); r.push_back({v, a.second}); v++; }
  return r;
}

int main()
{
  Arestas k5, k33, petersen, roda, prisma, k2n;
  for (int u = 0; u < 5; u++) for (int v = u + 1; v < 5; v++) k5.push_back({u, v});
  for (int u = 0; u < 3; u++) for (int v = 3; v < 6; v++) k33.push_back({u, v});
  for (int i = 0; i < 5; i++) { petersen.push_back({i, (i + 1) % 5}); petersen.push_back({i, i + 5}); petersen.push_back({i + 5, (i + 2) % 5 + 5}); }

  int v = 5;
  Arestas sk5 = subdivide(v, k5);
  cout << "K5 subdividido (" << v << " vertices): " << (testa(v, sk5) ? "planar" : "nao planar") << endl;
  v = 6;
  Arestas sk33 = subdivide(v, k33);
  cout << "K3,3 subdividido (" << v << " vertices): " << (testa(v, sk33) ? "planar" : "nao planar") << endl;

  int planaresK5 = 0, planaresK33 = 0;
  for (size_t i = 0; i < k5.size(); i++) { Arestas e = k5; e.erase(e.begin() + i); planaresK5 += testa(5, e); }
  for (size_t i = 0; i < k33.size(); i++) { Arestas e = k33; e.erase(e.begin() + i); planaresK33 += testa(6, e); }
  cout << "K5 menos uma aresta: planar em " << planaresK5 << " de " << k5.size() << " casos" << endl;
  cout << "K3,3 menos uma aresta: planar em " << planaresK33 << " de " << k33.size() << " casos" << endl;
  cout << "Petersen: " << (testa(10, petersen) ? "planar" : "nao planar") << endl;

  for (int k = 3; k <= 7; k++) {
    roda.clear(); prisma.clear(); k2n.clear();
    for (int i = 0; i < k; i++) {
      roda.push_back({i, (i + 1) % k}); roda.push_back({i, k});                 // ciclo + centro k
      prisma.push_back({i, (i + 1) % k}); prisma.push_back({k + i, k + (i + 1) % k}); prisma.push_back({i, k + i});
      k2n.push_back({0, 2 + i}); k2n.push_back({1, 2 + i});
    }
    cout << "k = " << k << ": roda " << (testa(k + 1, roda) ? "planar" : "nao planar")
         << ", prisma " << (testa(2 * k, prisma) ? "planar" : "nao planar")
         << ", K2," << k << " " << (testa(k + 2, k2n) ? "planar" : "nao planar") << endl;
  }
  return 0;
}
