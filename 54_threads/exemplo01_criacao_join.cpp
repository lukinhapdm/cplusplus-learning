/*
Exemplo 1. Threads (C++11 em diante, <thread>): fluxos de execucao dentro do MESMO processo, que
compartilham a memoria (variaveis globais e heap) e tem cada um sua propria pilha.
- std::thread t(funcao, argumentos...) cria e ja inicia a thread;
- t.join() espera a thread terminar (toda thread precisa de join ou detach antes de ser destruida);
- argumentos sao copiados; para passar por referencia use std::ref;
- std::this_thread::get_id() identifica a thread; a ordem de execucao entre threads NAO e garantida.
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtxSaida;   // so para as linhas do cout nao se misturarem (ver exemplo 2)

void trabalha(int id, int vezes)
{
  for (int i = 0; i < vezes; i++) {
    {
      lock_guard<mutex> trava(mtxSaida);
      cout << "thread " << id << ": passo " << i << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(10 * id));   // cada uma em um ritmo
  }
}

void quadrado(int x, int &resultado) { resultado = x * x; }   // devolve por referencia

int main()
{
  cout << "Nucleos: " << thread::hardware_concurrency() << endl;

  vector<thread> ts;
  for (int id = 1; id <= 3; id++) ts.emplace_back(trabalha, id, 3);   // cria 3 threads
  for (thread &t : ts) t.join();                                      // espera todas

  int r = 0;
  thread t(quadrado, 12, ref(r));   // sem ref, a thread alteraria uma copia
  t.join();
  cout << "12^2 = " << r << endl;

  int total = 0;
  thread lambda([&total]() { for (int i = 1; i <= 100; i++) total += i; });   // lambda capturando por referencia
  lambda.join();
  cout << "Soma 1..100 calculada pela thread: " << total << endl;
  return 0;
}
