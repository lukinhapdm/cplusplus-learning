/*
Exemplo 3. Produtor-consumidor com buffer limitado: produtores colocam itens numa fila de tamanho maximo
TAM e consumidores retiram. Alem da exclusao mutua (mutex), e preciso ESPERAR por uma condicao:
  - o produtor espera enquanto o buffer estiver cheio;
  - o consumidor espera enquanto estiver vazio.
condition_variable: wait(trava, condicao) libera o mutex e dorme ate ser avisado (notify) e a condicao valer;
evita a espera ocupada (laco testando sem parar). Item -1 sinaliza fim para os consumidores.
Compilar: g++ -std=c++17 -pthread arquivo.cpp
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
using namespace std;

const size_t TAM = 5;
queue<int> buffer;
mutex mtx;
condition_variable naoCheio, naoVazio;

void produtor(int id, int quantidade)
{
  for (int i = 0; i < quantidade; i++) {
    int item = id * 100 + i;
    unique_lock<mutex> trava(mtx);
    naoCheio.wait(trava, []() { return buffer.size() < TAM; });   // dorme se estiver cheio
    buffer.push(item);
    cout << "P" << id << " produziu " << item << " (buffer " << buffer.size() << ")" << endl;
    trava.unlock();
    naoVazio.notify_one();   // acorda um consumidor
  }
}

void consumidor(int id, long long &soma)
{
  while (true) {
    unique_lock<mutex> trava(mtx);
    naoVazio.wait(trava, []() { return !buffer.empty(); });   // dorme se estiver vazio
    int item = buffer.front(); buffer.pop();
    trava.unlock();
    naoCheio.notify_one();   // acorda um produtor
    if (item == -1) break;   // sinal de fim
    soma += item;
    lock_guard<mutex> t(mtx);
    cout << "    C" << id << " consumiu " << item << endl;
  }
}

int main()
{
  long long s1 = 0, s2 = 0;
  thread c1(consumidor, 1, ref(s1)), c2(consumidor, 2, ref(s2));
  thread p1(produtor, 1, 6), p2(produtor, 2, 6);
  p1.join(); p2.join();
  for (int i = 0; i < 2; i++) {   // um sinal de fim para cada consumidor
    unique_lock<mutex> trava(mtx);
    naoCheio.wait(trava, []() { return buffer.size() < TAM; });
    buffer.push(-1);
    trava.unlock();
    naoVazio.notify_one();
  }
  c1.join(); c2.join();
  long long esperado = 0;
  for (int id = 1; id <= 2; id++) for (int i = 0; i < 6; i++) esperado += id * 100 + i;
  cout << "Soma consumida: " << s1 + s2 << " (esperado " << esperado << ")" << endl;
  return 0;
}
