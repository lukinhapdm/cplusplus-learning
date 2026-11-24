/*
Exercicio 3. Exclusao mutua por anel de token: uma unica permissao (token) circula pelo anel; so quem esta com o
token pode entrar na secao critica. Quem nao precisa apenas repassa. Simples e justo (cada um espera no maximo
uma volta), mas o token circula mesmo sem pedidos e, se ele se perder, e preciso regenera-lo.
Simular com threads: cada processo precisa entrar na SC um numero diferente de vezes; o token para de circular
quando todos terminaram. Conferir a exclusao mutua e contar as passagens do token.
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
using namespace std;

const int N = 5;
int pedidos[N] = {2, 0, 3, 1, 2};   // quantas vezes cada processo quer a SC
int restante = 2 + 0 + 3 + 1 + 2;   // total de entradas que faltam (so mexe quem tem o token)
int comToken = 0;                   // quem esta com o token (simula a mensagem TOKEN chegando)
bool terminou = false;
mutex mtx;
condition_variable cv;
atomic<int> naSC(0), violacoes(0), passagens(0);

void processo(int id)
{
  while (true) {
    unique_lock<mutex> t(mtx);
    cv.wait(t, [id]() { return comToken == id || terminou; });   // espera o token chegar
    if (terminou) return;
    if (pedidos[id] > 0) {
      if (++naSC > 1) violacoes++;
      cout << "P" << id << " usa o token para entrar na SC" << endl;
      naSC--;
      pedidos[id]--;
      restante--;
    }
    if (restante == 0) { terminou = true; cv.notify_all(); return; }
    comToken = (id + 1) % N;   // passa o token ao sucessor
    passagens++;
    cv.notify_all();
  }
}

int main()
{
  vector<thread> ts;
  for (int i = 0; i < N; i++) ts.emplace_back(processo, i);
  for (thread &t : ts) t.join();
  cout << "Violacoes: " << violacoes << ", passagens do token: " << passagens << endl;
  return 0;
}
