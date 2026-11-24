/*
Exemplo 2. STL (Standard Template Library): containers, iteradores e algoritmos prontos.
- Sequenciais: vector (vetor dinamico), list (lista duplamente encadeada), deque (fila de duas pontas)
- Adaptadores: stack, queue, priority_queue
- Algoritmos (<algorithm>): sort, find, binary_search, reverse, count, ...
Os algoritmos trabalham com iteradores [inicio, fim), por isso servem para varios containers.
*/
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

template <typename Container>
void mostra(const string &nome, const Container &c)
{
  cout << nome << ": ";
  for (auto it = c.begin(); it != c.end(); ++it) cout << *it << " ";   // percorre com iterador
  cout << endl;
}

int main()
{
  // vector: acesso por indice O(1), insercao no final O(1) amortizado
  vector<int> v = {42, 7, 19, 3, 25};
  v.push_back(11);
  sort(v.begin(), v.end());
  mostra("vector ordenado", v);
  cout << "binary_search(19): " << binary_search(v.begin(), v.end(), 19) << endl;
  auto it = find(v.begin(), v.end(), 25);
  if (it != v.end()) cout << "find(25) na posicao " << it - v.begin() << endl;
  auto lb = lower_bound(v.begin(), v.end(), 20);   // primeira posicao >= 20
  cout << "lower_bound(20) aponta para " << *lb << endl;

  // list: insercao/remocao O(1) em qualquer ponto (com iterador), sem acesso por indice
  list<string> l = {"b", "d"};
  l.push_front("a");
  auto pos = l.begin(); ++pos; ++pos;   // aponta para "d"
  l.insert(pos, "c");
  mostra("list", l);

  // deque: insercao e remocao rapidas nas duas pontas
  deque<int> d;
  d.push_back(2); d.push_front(1); d.push_back(3);
  mostra("deque", d);

  // adaptadores: interface restrita sobre outro container
  stack<int> s; for (int x : v) s.push(x);
  cout << "stack (topo): " << s.top() << endl;
  queue<int> q; for (int x : v) q.push(x);
  cout << "queue (frente): " << q.front() << endl;
  priority_queue<int> pq(v.begin(), v.end());   // heap maximo
  cout << "priority_queue (maior): " << pq.top() << endl;

  reverse(v.begin(), v.end());
  mostra("vector invertido", v);
  return 0;
}
