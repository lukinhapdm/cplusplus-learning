/*
Exemplo 1. Forca bruta (busca exaustiva): gera TODAS as solucoes candidatas e testa cada uma.
Simples e sempre correta, mas o espaco de busca costuma ser exponencial:
  - subconjuntos de n itens: 2^n (aqui gerados contando de 0 a 2^n - 1; o bit i diz se o item i entra);
  - permutacoes de n itens: n! (next_permutation gera em ordem lexicografica).
Problemas: (a) soma de subconjuntos - existe subconjunto com soma alvo?
           (b) caixeiro viajante - menor ciclo que passa por todas as cidades.
*/
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

void somaSubconjuntos(int v[], int n, int alvo)
{
  int testados = 0, achados = 0;
  for (int mascara = 0; mascara < (1 << n); mascara++) {   // cada numero representa um subconjunto
    testados++;
    int soma = 0;
    for (int i = 0; i < n; i++) if (mascara & (1 << i)) soma += v[i];
    if (soma == alvo) {
      achados++;
      cout << "  { ";
      for (int i = 0; i < n; i++) if (mascara & (1 << i)) cout << v[i] << " ";
      cout << "}" << endl;
    }
  }
  cout << "  " << achados << " solucoes, " << testados << " subconjuntos testados" << endl;
}

void caixeiroViajante(int d[][5], int n)
{
  int perm[5], melhor[5], menor = INT_MAX, testadas = 0;
  for (int i = 0; i < n; i++) perm[i] = i;
  do {   // fixa a cidade 0 no inicio e permuta as outras: (n-1)! ciclos
    testadas++;
    int custo = 0;
    for (int i = 0; i < n; i++) custo += d[perm[i]][perm[(i + 1) % n]];
    if (custo < menor) { menor = custo; copy(perm, perm + n, melhor); }
  } while (next_permutation(perm + 1, perm + n));
  cout << "  melhor ciclo: ";
  for (int i = 0; i < n; i++) cout << melhor[i] << " -> ";
  cout << "0, custo " << menor << " (" << testadas << " permutacoes testadas)" << endl;
}

int main()
{
  int v[] = {3, 34, 4, 12, 5, 2};
  cout << "Subconjuntos de {3, 34, 4, 12, 5, 2} com soma 9:" << endl;
  somaSubconjuntos(v, 6, 9);

  int d[5][5] = {{0, 2, 9, 10, 7}, {2, 0, 6, 4, 3}, {9, 6, 0, 8, 5}, {10, 4, 8, 0, 6}, {7, 3, 5, 6, 0}};
  cout << "Caixeiro viajante com 5 cidades:" << endl;
  caixeiroViajante(d, 5);
  return 0;
}
