/*
Exercicio 2. Metodo da substituicao: chuta-se a forma da solucao e prova-se por inducao que ela vale.
Para T(n) = 2T(floor(n/2)) + n, T(1) = 1, o chute e T(n) <= c n log2 n para n >= 2.
Passo indutivo: T(n) <= 2 c (n/2) log2(n/2) + n = c n log2 n - c n + n <= c n log2 n se c >= 1.
A base (n = 2 e n = 3) exige T(2) = 4 <= 2c e T(3) = 5 <= 3c log2 3, ou seja, c >= 2.
O programa calcula T(n) para n ate 10^6 e confere numericamente que T(n) <= 2 n log2 n, e mostra
que c = 1 nao serve por causa da base.
*/
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
  const int N = 1000000;
  vector<long long> T(N + 1);
  T[1] = 1;
  for (int n = 2; n <= N; n++) T[n] = 2 * T[n / 2] + n;   // calcula de baixo para cima

  for (double c : {1.0, 2.0}) {
    int violacoes = 0, primeira = -1;
    for (int n = 2; n <= N; n++)
      if (T[n] > c * n * log2((double)n)) { violacoes++; if (primeira < 0) primeira = n; }
    cout << "c = " << c << ": " << violacoes << " violacoes";
    if (primeira > 0) cout << " (primeira em n = " << primeira << ", T = " << T[primeira] << ")";
    cout << endl;
  }
  double maxRazao = 0;
  for (int n = 2; n <= N; n++) maxRazao = max(maxRazao, T[n] / (n * log2((double)n)));
  cout << "Maior razao T(n) / (n log2 n): " << maxRazao << endl;
  return 0;
}
