/*
Exemplo 2. Memoria virtual: o programa enxerga um espaco de enderecamento grande, dividido em paginas;
so algumas paginas ficam na memoria principal (molduras). Acessar uma pagina ausente gera uma
falta de pagina e ela precisa ser trazida do disco, substituindo outra. Politicas de substituicao:
- FIFO: sai a pagina que entrou ha mais tempo;
- LRU (least recently used): sai a pagina usada ha mais tempo (aproveita a localidade de referencia).
O mesmo raciocinio vale para o buffer de paginas usado por arvores B e arquivos.
*/
#include <iostream>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int fifo(const int ref[], int n, int molduras)
{
  queue<int> ordem;
  unordered_set<int> naMemoria;
  int faltas = 0;
  for (int i = 0; i < n; i++) {
    if (naMemoria.count(ref[i])) continue;   // acerto
    faltas++;
    if ((int)naMemoria.size() == molduras) {  // memoria cheia: tira o mais antigo
      naMemoria.erase(ordem.front());
      ordem.pop();
    }
    ordem.push(ref[i]);
    naMemoria.insert(ref[i]);
  }
  return faltas;
}

int lru(const int ref[], int n, int molduras)
{
  list<int> uso;   // frente = usada mais recentemente
  unordered_map<int, list<int>::iterator> pos;
  int faltas = 0;
  for (int i = 0; i < n; i++) {
    int p = ref[i];
    if (pos.count(p)) uso.erase(pos[p]);   // acerto: vai para a frente
    else {
      faltas++;
      if ((int)uso.size() == molduras) { pos.erase(uso.back()); uso.pop_back(); }   // sai a menos recente
    }
    uso.push_front(p);
    pos[p] = uso.begin();
  }
  return faltas;
}

int main()
{
  int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};   // paginas acessadas
  int n = sizeof(ref) / sizeof(ref[0]);
  cout << "Molduras\tFIFO\tLRU" << endl;
  for (int m = 1; m <= 5; m++) cout << m << "\t\t" << fifo(ref, n, m) << "\t" << lru(ref, n, m) << endl;
  return 0;
}
