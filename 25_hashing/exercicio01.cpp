/*
Exercicio 1. Tabela hash com sondagem linear que cresce sozinha: quando o fator de carga (n/M)
passar de 0.7, criar uma tabela com aproximadamente o dobro do tamanho (primo) e reinserir as chaves (rehash).
*/
#include <iostream>
using namespace std;

const int VAZIO = -1;

bool primo(int x)
{
  if (x < 2) return false;
  for (int d = 2; d * d <= x; d++) if (x % d == 0) return false;
  return true;
}

class HashDinamico {
  int *t, M, n;

  void insereSemCrescer(int k)
  {
    int p = k % M;
    while (t[p] != VAZIO) p = (p + 1) % M;
    t[p] = k; n++;
  }

  void rehash()
  {
    int *velha = t, Mvelho = M;
    M = 2 * M + 1;
    while (!primo(M)) M++;   // proximo primo
    t = new int[M]; n = 0;
    for (int i = 0; i < M; i++) t[i] = VAZIO;
    for (int i = 0; i < Mvelho; i++) if (velha[i] != VAZIO) insereSemCrescer(velha[i]);
    delete[] velha;
    cout << "  rehash: novo tamanho " << M << endl;
  }

public:
  HashDinamico(int tam = 5) : M(tam), n(0)
  {
    t = new int[M];
    for (int i = 0; i < M; i++) t[i] = VAZIO;
  }
  ~HashDinamico() { delete[] t; }

  void insere(int k)
  {
    if ((double)(n + 1) / M > 0.7) rehash();
    insereSemCrescer(k);
  }

  void imprime()
  {
    cout << "M = " << M << ", n = " << n << ": ";
    for (int i = 0; i < M; i++) if (t[i] != VAZIO) cout << "[" << i << "]" << t[i] << " ";
    cout << endl;
  }
};

int main()
{
  HashDinamico h;
  for (int k = 7; k <= 70; k += 7) { cout << "insere " << k << endl; h.insere(k); }
  h.imprime();
  return 0;
}
