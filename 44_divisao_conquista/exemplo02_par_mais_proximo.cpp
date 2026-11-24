/*
Exemplo 2. Par de pontos mais proximo no plano por divisao e conquista.
1) Ordena os pontos por x e divide em duas metades por uma reta vertical.
2) Resolve cada metade: menor distancia d = min(dEsq, dDir).
3) Combina: o par mais proximo pode cruzar a reta; so interessam os pontos a menos de d da reta (faixa).
   Ordenados por y, cada ponto da faixa so precisa ser comparado com os poucos (no maximo 7) seguintes
   cuja diferenca em y seja menor que d.
Com a faixa ordenada por y via intercalacao, T(n) = 2T(n/2) + O(n) = O(n log n); forca bruta e O(n^2).
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cfloat>
using namespace std;

struct Ponto { double x, y; };
double dist(const Ponto &a, const Ponto &b) { return hypot(a.x - b.x, a.y - b.y); }
long long comparacoes;

// p ordenado por x no intervalo [ini, fim); ao sair, p[ini..fim) fica ordenado por y
double maisProximo(vector<Ponto> &p, int ini, int fim, vector<Ponto> &aux)
{
  if (fim - ini <= 3) {   // caso base: forca bruta e ordena por y
    double d = DBL_MAX;
    for (int i = ini; i < fim; i++)
      for (int j = i + 1; j < fim; j++) { comparacoes++; d = min(d, dist(p[i], p[j])); }
    sort(p.begin() + ini, p.begin() + fim, [](const Ponto &a, const Ponto &b) { return a.y < b.y; });
    return d;
  }
  int meio = (ini + fim) / 2;
  double xMeio = p[meio].x;
  double d = min(maisProximo(p, ini, meio, aux), maisProximo(p, meio, fim, aux));

  merge(p.begin() + ini, p.begin() + meio, p.begin() + meio, p.begin() + fim, aux.begin(),
        [](const Ponto &a, const Ponto &b) { return a.y < b.y; });   // intercala por y
  copy(aux.begin(), aux.begin() + (fim - ini), p.begin() + ini);

  vector<Ponto> faixa;
  for (int i = ini; i < fim; i++) if (fabs(p[i].x - xMeio) < d) faixa.push_back(p[i]);
  for (size_t i = 0; i < faixa.size(); i++)
    for (size_t j = i + 1; j < faixa.size() && faixa[j].y - faixa[i].y < d; j++) {
      comparacoes++;
      d = min(d, dist(faixa[i], faixa[j]));
    }
  return d;
}

int main()
{
  srand(9);
  int n = 5000;
  vector<Ponto> p(n);
  for (Ponto &q : p) q = {rand() % 100000 / 10.0, rand() % 100000 / 10.0};

  double bruta = DBL_MAX;
  long long compBruta = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) { compBruta++; bruta = min(bruta, dist(p[i], p[j])); }

  sort(p.begin(), p.end(), [](const Ponto &a, const Ponto &b) { return a.x < b.x; });
  vector<Ponto> aux(n);
  comparacoes = 0;
  double dc = maisProximo(p, 0, n, aux);
  cout << "Forca bruta: " << bruta << " (" << compBruta << " distancias)" << endl;
  cout << "D&C:         " << dc << " (" << comparacoes << " distancias)" << endl;
  return 0;
}
