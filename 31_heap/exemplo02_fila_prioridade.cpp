/*
Exemplo 2. Fila de prioridade: cada elemento tem uma prioridade e sai primeiro o de maior prioridade.
O heap e a implementacao classica. Aqui: (a) heap generico com template e comparador;
(b) a mesma coisa com priority_queue da STL.
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Tarefa { string nome; int prioridade; };

// Menor(a, b) = true quando a tem MENOS prioridade que b (mesma convencao da STL)
struct Menor {
  bool operator()(const Tarefa &a, const Tarefa &b) const { return a.prioridade < b.prioridade; }
};

template <typename T, typename Comp>
class FilaPrioridade {
  vector<T> v;
  Comp menor;
public:
  bool vazia() const { return v.empty(); }
  const T &topo() const { return v[0]; }

  void insere(const T &x)
  {
    v.push_back(x);
    int i = v.size() - 1;
    while (i > 0 && menor(v[(i - 1) / 2], v[i])) { swap(v[i], v[(i - 1) / 2]); i = (i - 1) / 2; }
  }

  T remove()
  {
    T x = v[0];
    v[0] = v.back(); v.pop_back();
    int i = 0, n = v.size();
    while (2 * i + 1 < n) {
      int f = 2 * i + 1;
      if (f + 1 < n && menor(v[f], v[f + 1])) f++;
      if (!menor(v[i], v[f])) break;
      swap(v[i], v[f]); i = f;
    }
    return x;
  }
};

int main()
{
  Tarefa ts[] = {{"backup", 2}, {"incendio", 10}, {"email", 1}, {"cliente", 7}, {"reuniao", 5}};

  FilaPrioridade<Tarefa, Menor> fp;
  for (const Tarefa &t : ts) fp.insere(t);
  cout << "Nossa fila: ";
  while (!fp.vazia()) { Tarefa t = fp.remove(); cout << t.nome << "(" << t.prioridade << ") "; }
  cout << endl;

  priority_queue<Tarefa, vector<Tarefa>, Menor> pq;   // STL: tipo, container, comparador
  for (const Tarefa &t : ts) pq.push(t);
  cout << "STL:       ";
  while (!pq.empty()) { cout << pq.top().nome << "(" << pq.top().prioridade << ") "; pq.pop(); }
  cout << endl;

  priority_queue<int, vector<int>, greater<int>> minimo;   // greater -> heap minimo
  for (int x : {5, 1, 9, 3}) minimo.push(x);
  cout << "Heap minimo STL: ";
  while (!minimo.empty()) { cout << minimo.top() << " "; minimo.pop(); }
  cout << endl;
  return 0;
}
