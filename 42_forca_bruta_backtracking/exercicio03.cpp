/*
Exercicio 3. Gerar com backtracking: (a) todas as combinacoes de k elementos de {1..n} (C(n, k) delas);
(b) todas as permutacoes de uma palavra SEM repeticoes, mesmo quando ha letras repetidas
(ordena as letras e, no mesmo nivel, nao tenta duas vezes a mesma letra).
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n, k, comb[20], total;

void combinacoes(int pos, int inicio)
{
  if (pos == k) {
    total++;
    for (int i = 0; i < k; i++) cout << comb[i] << (i + 1 < k ? "," : " ");
    return;
  }
  for (int x = inicio; x <= n - (k - pos) + 1; x++) {   // poda: precisa sobrar elementos suficientes
    comb[pos] = x;
    combinacoes(pos + 1, x + 1);
  }
}

string palavra, atual;
bool usado[20];

void permutacoes()
{
  if (atual.size() == palavra.size()) { cout << atual << " "; total++; return; }
  for (size_t i = 0; i < palavra.size(); i++) {
    if (usado[i]) continue;
    if (i > 0 && palavra[i] == palavra[i - 1] && !usado[i - 1]) continue;   // evita repeticao
    usado[i] = true; atual.push_back(palavra[i]);
    permutacoes();
    usado[i] = false; atual.pop_back();
  }
}

int main()
{
  n = 5; k = 3; total = 0;
  cout << "C(5,3): ";
  combinacoes(0, 1);
  cout << "-> " << total << endl;

  palavra = "arara"; total = 0;
  sort(palavra.begin(), palavra.end());
  cout << "Permutacoes distintas de arara: ";
  permutacoes();
  cout << "-> " << total << " (5! / (3! 2!) = 10)" << endl;
  return 0;
}
