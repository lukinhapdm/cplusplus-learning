/*
Exercicio 3. Escalonamento para minimizar o atraso maximo: cada tarefa tem duracao e prazo; executando
uma de cada vez a partir do tempo 0, o atraso de uma tarefa e max(0, termino - prazo).
Guloso otimo: ordem do prazo mais cedo (Earliest Deadline First). Conferir comparando com todas as
permutacoes (forca bruta) e com a ordem "mais curta primeiro", que nao e otima.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tarefa { char nome; int duracao, prazo; };

int atrasoMaximo(const vector<Tarefa> &ordem)
{
  int t = 0, pior = 0;
  for (const Tarefa &x : ordem) { t += x.duracao; pior = max(pior, t - x.prazo); }
  return pior;
}

void mostra(const char *nome, const vector<Tarefa> &o)
{
  cout << nome << ": ";
  for (const Tarefa &x : o) cout << x.nome;
  cout << " -> atraso maximo " << atrasoMaximo(o) << endl;
}

int main()
{
  vector<Tarefa> t = {{'A', 3, 6}, {'B', 2, 8}, {'C', 1, 9}, {'D', 4, 9}, {'E', 3, 14}, {'F', 2, 15}};

  vector<Tarefa> edf = t;
  sort(edf.begin(), edf.end(), [](const Tarefa &a, const Tarefa &b) { return a.prazo < b.prazo; });
  mostra("Prazo mais cedo   ", edf);

  vector<Tarefa> curta = t;
  sort(curta.begin(), curta.end(), [](const Tarefa &a, const Tarefa &b) { return a.duracao < b.duracao; });
  mostra("Mais curta antes  ", curta);

  vector<Tarefa> p = t, melhor = t;
  sort(p.begin(), p.end(), [](const Tarefa &a, const Tarefa &b) { return a.nome < b.nome; });
  do { if (atrasoMaximo(p) < atrasoMaximo(melhor)) melhor = p; }
  while (next_permutation(p.begin(), p.end(), [](const Tarefa &a, const Tarefa &b) { return a.nome < b.nome; }));
  mostra("Forca bruta (720) ", melhor);
  return 0;
}
