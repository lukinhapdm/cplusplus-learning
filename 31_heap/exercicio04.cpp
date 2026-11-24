/*
Exercicio 4. Simular o atendimento de um pronto-socorro: pacientes chegam com gravidade de 1 a 5 e
sao atendidos pela maior gravidade; em caso de empate, por ordem de chegada. Usar um heap proprio
(sem STL) cujo criterio compara gravidade e, no empate, o numero de chegada.
*/
#include <iostream>
#include <utility>
#include <string>
using namespace std;

struct Paciente { string nome; int gravidade, chegada; };

// a tem prioridade maior que b?
bool antes(const Paciente &a, const Paciente &b)
{
  if (a.gravidade != b.gravidade) return a.gravidade > b.gravidade;
  return a.chegada < b.chegada;   // empate: quem chegou primeiro
}

const int MAX = 50;
Paciente heap[MAX];
int n = 0, contador = 0;

void chega(string nome, int g)
{
  heap[n] = {nome, g, contador++};
  int i = n++;
  while (i > 0 && antes(heap[i], heap[(i - 1) / 2])) { swap(heap[i], heap[(i - 1) / 2]); i = (i - 1) / 2; }
  cout << "Chegou " << nome << " (gravidade " << g << ")" << endl;
}

void atende()
{
  Paciente p = heap[0];
  heap[0] = heap[--n];
  int i = 0;
  while (2 * i + 1 < n) {
    int f = 2 * i + 1;
    if (f + 1 < n && antes(heap[f + 1], heap[f])) f++;
    if (!antes(heap[f], heap[i])) break;
    swap(heap[i], heap[f]); i = f;
  }
  cout << "  Atendendo " << p.nome << " (gravidade " << p.gravidade << ")" << endl;
}

int main()
{
  chega("Ana", 2); chega("Beto", 5); chega("Caio", 2); chega("Dora", 4);
  atende(); atende();
  chega("Edu", 5); chega("Fabi", 2);
  while (n > 0) atende();
  return 0;
}
