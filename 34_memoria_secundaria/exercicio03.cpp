/*
Exercicio 3. Implementar a politica de substituicao otima (OPT, de Belady): sai a pagina que vai demorar
mais para ser usada de novo (nao e realizavel na pratica, mas serve de referencia). Comparar com FIFO e
mostrar a anomalia de Belady: com FIFO, aumentar o numero de molduras pode AUMENTAR as faltas.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int fifo(const vector<int> &ref, int m)
{
  vector<int> mem;   // em ordem de chegada
  int faltas = 0;
  for (int p : ref) {
    if (find(mem.begin(), mem.end(), p) != mem.end()) continue;
    faltas++;
    if ((int)mem.size() == m) mem.erase(mem.begin());
    mem.push_back(p);
  }
  return faltas;
}

int otimo(const vector<int> &ref, int m)
{
  vector<int> mem;
  int faltas = 0;
  for (size_t i = 0; i < ref.size(); i++) {
    if (find(mem.begin(), mem.end(), ref[i]) != mem.end()) continue;
    faltas++;
    if ((int)mem.size() < m) { mem.push_back(ref[i]); continue; }
    int vitima = 0, maisLonge = -1;
    for (size_t j = 0; j < mem.size(); j++) {   // quando cada pagina sera usada de novo?
      size_t prox = i + 1;
      while (prox < ref.size() && ref[prox] != mem[j]) prox++;
      if ((int)prox > maisLonge) { maisLonge = prox; vitima = j; }
    }
    mem[vitima] = ref[i];
  }
  return faltas;
}

int main()
{
  vector<int> ref = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};   // sequencia classica da anomalia
  cout << "Molduras\tFIFO\tOTIMO" << endl;
  for (int m = 1; m <= 5; m++) cout << m << "\t\t" << fifo(ref, m) << "\t" << otimo(ref, m) << endl;
  cout << "Repare: FIFO com 4 molduras tem mais faltas que com 3 (anomalia de Belady)." << endl;
  return 0;
}
