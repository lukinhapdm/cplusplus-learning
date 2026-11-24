/*
Exemplo 1. Programacao dinamica (PD): para problemas com
  (1) subestrutura otima - a solucao otima usa solucoes otimas de subproblemas, e
  (2) subproblemas sobrepostos - os mesmos subproblemas aparecem muitas vezes na recursao,
resolve cada subproblema UMA vez e guarda a resposta numa tabela. Duas formas:
  - de cima para baixo (memorizacao): a recursao normal, consultando/guardando na tabela;
  - de baixo para cima: preenche a tabela a partir dos casos base, sem recursao.
Diferente de divisao e conquista, em que os subproblemas sao independentes.
Exemplo classico: Fibonacci. Tambem: numero de caminhos numa grade (so andando para direita/baixo).
*/
#include <iostream>
#include <vector>
using namespace std;

long long chamadas;

long long fibRec(int n) { chamadas++; return n < 2 ? n : fibRec(n - 1) + fibRec(n - 2); }

long long fibMemo(int n, vector<long long> &memo)
{
  chamadas++;
  if (n < 2) return n;
  if (memo[n] != -1) return memo[n];             // ja calculado
  return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
}

long long fibTabela(int n)
{
  vector<long long> f(n + 2);
  f[0] = 0; f[1] = 1;
  for (int i = 2; i <= n; i++) f[i] = f[i - 1] + f[i - 2];   // casos base para cima
  return f[n];
}

// caminhos[l][c] = caminhos[l-1][c] + caminhos[l][c-1]; casas com obstaculo valem 0
long long caminhosGrade(int L, int C, const vector<vector<int>> &obst)
{
  vector<vector<long long>> t(L, vector<long long>(C, 0));
  for (int l = 0; l < L; l++)
    for (int c = 0; c < C; c++) {
      if (obst[l][c]) continue;
      if (l == 0 && c == 0) t[l][c] = 1;
      else t[l][c] = (l > 0 ? t[l - 1][c] : 0) + (c > 0 ? t[l][c - 1] : 0);
    }
  return t[L - 1][C - 1];
}

int main()
{
  int n = 35;
  chamadas = 0; long long a = fibRec(n); long long ca = chamadas;
  vector<long long> memo(n + 1, -1);
  chamadas = 0; long long b = fibMemo(n, memo); long long cb = chamadas;
  cout << "fib(" << n << ") recursivo:    " << a << " com " << ca << " chamadas" << endl;
  cout << "fib(" << n << ") memorizacao:  " << b << " com " << cb << " chamadas" << endl;
  cout << "fib(" << n << ") tabela:       " << fibTabela(n) << " com " << n - 1 << " somas" << endl;
  cout << "fib(90) tabela:       " << fibTabela(90) << endl;

  vector<vector<int>> obst(5, vector<int>(6, 0));
  cout << "\nCaminhos em grade 5x6 sem obstaculos: " << caminhosGrade(5, 6, obst) << " (C(9,4) = 126)" << endl;
  obst[1][1] = obst[2][3] = obst[3][2] = 1;
  cout << "Com 3 obstaculos: " << caminhosGrade(5, 6, obst) << endl;
  return 0;
}
