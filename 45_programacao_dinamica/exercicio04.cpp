/*
Exercicio 4. Maior subsequencia crescente (LIS): os elementos nao precisam ser contiguos.
  (a) PD O(n^2): L[i] = 1 + max(L[j]) para j < i com v[j] < v[i]; guarda o anterior para reconstruir.
  (b) O(n log n): fim[t] = menor final possivel de uma subsequencia crescente de tamanho t+1;
      para cada v[i], busca binaria (lower_bound) da posicao que ele substitui.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

vector<int> lisQuadratica(const vector<int> &v)
{
  int n = v.size(), melhor = 0;
  vector<int> L(n, 1), ant(n, -1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++)
      if (v[j] < v[i] && L[j] + 1 > L[i]) { L[i] = L[j] + 1; ant[i] = j; }
    if (L[i] > L[melhor]) melhor = i;
  }
  vector<int> r;
  for (int i = melhor; i != -1; i = ant[i]) r.push_back(v[i]);
  reverse(r.begin(), r.end());
  return r;
}

int lisRapida(const vector<int> &v)
{
  vector<int> fim;
  for (int x : v) {
    auto it = lower_bound(fim.begin(), fim.end(), x);
    if (it == fim.end()) fim.push_back(x);   // estende a maior
    else *it = x;                            // melhora (diminui) um final
  }
  return fim.size();
}

int main()
{
  vector<int> v = {10, 22, 9, 33, 21, 50, 41, 60, 80, 3};
  vector<int> r = lisQuadratica(v);
  cout << "LIS: ";
  for (int x : r) cout << x << " ";
  cout << "(tamanho " << r.size() << ", versao rapida: " << lisRapida(v) << ")" << endl;

  srand(4);
  int erros = 0;
  for (int t = 0; t < 500; t++) {
    vector<int> w(1 + rand() % 60);
    for (int &x : w) x = rand() % 100;
    if ((int)lisQuadratica(w).size() != lisRapida(w)) erros++;
  }
  cout << "500 testes aleatorios: " << erros << " diferencas" << endl;
  return 0;
}
