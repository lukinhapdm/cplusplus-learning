/*
Exercicio 3. SOMA DE SUBCONJUNTOS e NP-completo, mas tem algoritmo pseudo-polinomial por programacao
dinamica: pode[s] = existe subconjunto com soma s, custo O(n * alvo). Isso nao prova P = NP porque o tamanho
da entrada e proporcional a log(alvo), e nao a alvo: com numeros de muitos digitos a tabela fica exponencial.
Comparar com a forca bruta 2^n para n = 20 e mostrar como a tabela cresce quando os numeros crescem.
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

bool pd(const vector<long long> &v, long long alvo, long long &operacoes)
{
  vector<bool> pode(alvo + 1, false);
  pode[0] = true;
  operacoes = 0;
  for (long long x : v)
    for (long long s = alvo; s >= x; s--) {   // de tras para frente: cada item usado no maximo uma vez
      operacoes++;
      if (pode[s - x]) pode[s] = true;
    }
  return pode[alvo];
}

bool forcaBruta(const vector<long long> &v, long long alvo, long long &operacoes)
{
  int n = v.size();
  operacoes = 0;
  bool achou = false;
  for (long long mask = 0; mask < (1LL << n); mask++) {
    long long s = 0;
    for (int i = 0; i < n; i++) if (mask >> i & 1) s += v[i];
    operacoes++;
    if (s == alvo) achou = true;
  }
  return achou;
}

int main()
{
  srand(3);
  for (long long maximo : {100LL, 10000LL, 1000000LL}) {
    vector<long long> v(20);
    long long soma = 0;
    for (auto &x : v) { x = 1 + ((long long)rand() * 32768 + rand()) % maximo; soma += x; }
    long long alvo = soma / 3, opPD, opFB;
    bool a = pd(v, alvo, opPD), b = forcaBruta(v, alvo, opFB);
    cout << "numeros ate " << maximo << ", alvo " << alvo << ": " << (a ? "existe" : "nao existe")
         << (a == b ? "" : " (DIVERGE!)") << " | PD: " << opPD << " operacoes, forca bruta: " << opFB << endl;
  }
  return 0;
}
