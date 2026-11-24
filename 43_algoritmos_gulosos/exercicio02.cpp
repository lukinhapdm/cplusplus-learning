/*
Exercicio 2. Particionamento de intervalos (alocacao de salas): todas as aulas precisam acontecer;
usar o menor numero de salas sem duas aulas sobrepostas na mesma sala.
Guloso: processar as aulas pela hora de INICIO; colocar cada uma na sala que vagou primeiro (heap minimo
com o horario de termino de cada sala) ou abrir uma sala nova. O numero de salas e igual a
profundidade maxima (maior quantidade de aulas acontecendo ao mesmo tempo), que e um limite inferior.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Aula { int ini, fim, sala; };

int main()
{
  vector<Aula> aulas = {{9, 11, 0}, {9, 10, 0}, {9, 13, 0}, {11, 13, 0}, {11, 12, 0}, {13, 15, 0},
                        {14, 16, 0}, {14, 15, 0}, {15, 17, 0}, {10, 12, 0}};
  sort(aulas.begin(), aulas.end(), [](const Aula &a, const Aula &b) { return a.ini < b.ini; });

  typedef pair<int, int> Sala;   // (horario em que fica livre, numero da sala)
  priority_queue<Sala, vector<Sala>, greater<Sala>> livres;
  int salas = 0;
  for (Aula &a : aulas) {
    if (!livres.empty() && livres.top().first <= a.ini) {   // a sala que vagou primeiro ja esta livre
      a.sala = livres.top().second;
      livres.pop();
    } else a.sala = ++salas;                                // abre uma sala nova
    livres.push(Sala(a.fim, a.sala));
  }
  for (const Aula &a : aulas) cout << "[" << a.ini << "h, " << a.fim << "h) -> sala " << a.sala << endl;

  int profundidade = 0;   // conferencia: maximo de aulas simultaneas
  for (int t = 0; t < 24; t++) {
    int c = 0;
    for (const Aula &a : aulas) if (a.ini <= t && t < a.fim) c++;
    profundidade = max(profundidade, c);
  }
  cout << "Salas usadas: " << salas << ", profundidade maxima: " << profundidade << endl;
  return 0;
}
