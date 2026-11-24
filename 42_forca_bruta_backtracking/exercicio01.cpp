/*
Exercicio 1. Soma de subconjuntos com backtracking e poda. Com os valores em ordem crescente, um ramo
pode ser abandonado quando (a) a soma parcial + o proximo valor ja passa do alvo, ou (b) a soma parcial +
tudo o que resta nao alcanca o alvo. Comparar os nos visitados com os 2^n subconjuntos da forca bruta.
(Valores repetidos no vetor geram subconjuntos iguais vindos de posicoes diferentes.)
*/
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n, alvo, v[30], resto[31];
bool escolhido[30];
long long nos, solucoes;

void tenta(int i, int soma)
{
  nos++;
  if (soma == alvo) {
    if (++solucoes <= 3) {   // mostra as 3 primeiras
      cout << "  { ";
      for (int j = 0; j < i; j++) if (escolhido[j]) cout << v[j] << " ";
      cout << "}" << endl;
    }
    return;
  }
  if (i == n) return;
  if (soma + v[i] > alvo) return;            // poda (a): valores crescentes, nenhum outro cabe
  if (soma + resto[i] < alvo) return;        // poda (b): nem somando tudo chega
  escolhido[i] = true;  tenta(i + 1, soma + v[i]);   // inclui v[i]
  escolhido[i] = false; tenta(i + 1, soma);          // nao inclui v[i]
}

int main()
{
  srand(6);
  n = 25;
  for (int i = 0; i < n; i++) v[i] = 1 + rand() % 100;
  sort(v, v + n);
  resto[n] = 0;
  for (int i = n - 1; i >= 0; i--) resto[i] = resto[i + 1] + v[i];   // soma de v[i..n-1]
  alvo = 150;
  tenta(0, 0);
  cout << solucoes << " subconjuntos com soma " << alvo << "; nos visitados: " << nos
       << " (forca bruta: " << (1LL << n) << " subconjuntos)" << endl;
  return 0;
}
