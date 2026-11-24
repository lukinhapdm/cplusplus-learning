/*
Exercicio 2. Jantar dos filosofos: 5 filosofos em volta da mesa, um garfo (mutex) entre cada dois; para comer,
cada um precisa dos dois garfos vizinhos. Se todos pegarem primeiro o garfo da esquerda, pode ocorrer
DEADLOCK (cada um segura um garfo e espera o outro para sempre).
Solucao: quebrar a espera circular impondo uma ordem global - cada filosofo pega primeiro o garfo de MENOR numero.
(Outra opcao em C++17: std::scoped_lock trava varios mutexes de uma vez sem deadlock.)
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;

const int F = 5, REFEICOES = 3;
mutex garfo[F], saida;
int comeu[F];

void filosofo(int id)
{
  int esq = id, dir = (id + 1) % F;
  int primeiro = min(esq, dir), segundo = max(esq, dir);   // ordem global evita a espera circular
  for (int r = 0; r < REFEICOES; r++) {
    this_thread::sleep_for(chrono::milliseconds(5));        // pensando
    lock_guard<mutex> a(garfo[primeiro]);
    lock_guard<mutex> b(garfo[segundo]);
    comeu[id]++;
    {
      lock_guard<mutex> s(saida);
      cout << "Filosofo " << id << " come com os garfos " << primeiro << " e " << segundo << " (refeicao " << r + 1 << ")" << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(5));        // comendo
  }                                                          // os garfos sao soltos ao sair do escopo
}

int main()
{
  vector<thread> ts;
  for (int i = 0; i < F; i++) ts.emplace_back(filosofo, i);
  for (thread &t : ts) t.join();
  cout << "Todos comeram " << REFEICOES << " vezes, sem deadlock:";
  for (int i = 0; i < F; i++) cout << " " << comeu[i];
  cout << endl;
  return 0;
}
