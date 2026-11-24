/*
Exercicio 3. Mostrar o efeito do agrupamento primario: inserir as mesmas 700 chaves aleatorias em uma
tabela de tamanho 1009 com sondagem linear e com hash duplo, e comparar a media de acessos
de uma busca com sucesso.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

const int M = 1009;   // primo
const int VAZIO = -1;

int h1(int k) { return k % M; }
int h2(int k) { return 1 + k % (M - 2); }

int insere(int t[], int k, bool dupla)
{
  int passo = dupla ? h2(k) : 1, p = h1(k), acessos = 1;
  while (t[p] != VAZIO) { p = (p + passo) % M; acessos++; }
  t[p] = k;
  return acessos;   // acessos da insercao = acessos da futura busca com sucesso
}

int main()
{
  int lin[M], dup[M];
  for (int i = 0; i < M; i++) lin[i] = dup[i] = VAZIO;
  srand(42);
  long totalLin = 0, totalDup = 0;
  int n = 700;
  for (int i = 0; i < n; i++) {
    int k = rand() % 1000000;
    totalLin += insere(lin, k, false);
    totalDup += insere(dup, k, true);
  }
  double alfa = (double)n / M;
  cout << "Fator de carga: " << alfa << endl;
  cout << "Linear: " << (double)totalLin / n << " acessos (teoria: " << 0.5 * (1 + 1 / (1 - alfa)) << ")" << endl;
  cout << "Dupla:  " << (double)totalDup / n << " acessos" << endl;
  return 0;
}
