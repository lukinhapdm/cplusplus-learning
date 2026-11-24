/*
Exemplo 2. Replicacao com quorum: o arquivo tem N replicas (em servidores diferentes) para tolerar falhas.
Cada escrita grava em W replicas e incrementa o numero de versao; cada leitura consulta R replicas e fica
com a de maior versao. Se R + W > N, todo conjunto de leitura intercepta o ultimo conjunto de escrita,
entao a leitura SEMPRE ve a versao mais recente; e se W > N / 2, duas escritas nao conflitam.
Simular muitas escritas e leituras em replicas aleatorias e contar leituras desatualizadas para varias (R, W).
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int N = 5;

// escolhe k replicas distintas ao acaso
vector<int> sorteia(int k)
{
  vector<int> r(N);
  for (int i = 0; i < N; i++) r[i] = i;
  for (int i = 0; i < k; i++) swap(r[i], r[i + rand() % (N - i)]);
  r.resize(k);
  return r;
}

int main()
{
  srand(1);
  printf("  R  W  R+W>N  leituras desatualizadas\n");
  int casos[][2] = {{1, 5}, {5, 1}, {3, 3}, {2, 4}, {2, 3}, {1, 1}, {2, 2}};
  for (auto &c : casos) {
    int R = c[0], W = c[1];
    vector<int> versao(N, 0);
    int atual = 0, velhas = 0, leituras = 0;
    for (int op = 0; op < 10000; op++) {
      if (rand() % 2) {   // escrita
        atual++;
        for (int r : sorteia(W)) versao[r] = atual;
      } else {            // leitura: fica com a maior versao entre as R consultadas
        int lida = 0;
        for (int r : sorteia(R)) lida = max(lida, versao[r]);
        leituras++;
        if (lida != atual) velhas++;
      }
    }
    printf("  %d  %d  %-5s  %5d de %d\n", R, W, R + W > N ? "sim" : "nao", velhas, leituras);
  }
  return 0;
}
