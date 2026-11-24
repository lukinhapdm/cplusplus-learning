/*
Exemplo 1. Analise de algoritmos: medir o custo contando operacoes relevantes (comparacoes, atribuicoes...)
em funcao do tamanho n da entrada, em vez de medir tempo (que depende da maquina).
- Melhor caso, pior caso e caso medio: a mesma entrada de tamanho n pode custar diferente.
- Tecnica de projeto: pequenas ideias mudam o custo. Ex.: achar maximo E minimo
  * ingenuo: 2(n - 1) comparacoes;
  * comparando aos pares: cerca de 3n/2 comparacoes (o menor do par so concorre ao minimo).
*/
#include <iostream>
#include <cstdlib>
using namespace std;

void maxMinIngenuo(int v[], int n, int &mx, int &mn, long long &comp)
{
  mx = mn = v[0];
  comp = 0;
  for (int i = 1; i < n; i++) {
    comp++; if (v[i] > mx) mx = v[i];
    comp++; if (v[i] < mn) mn = v[i];
  }
}

void maxMinPares(int v[], int n, int &mx, int &mn, long long &comp)
{
  comp = 0;
  int i;
  if (n % 2) { mx = mn = v[0]; i = 1; }   // n impar: comeca com o primeiro
  else { comp++; if (v[0] > v[1]) { mx = v[0]; mn = v[1]; } else { mx = v[1]; mn = v[0]; } i = 2; }
  for (; i + 1 < n; i += 2) {
    int maior = v[i], menor = v[i + 1];
    comp++; if (menor > maior) { maior = v[i + 1]; menor = v[i]; }   // 1 comparacao dentro do par
    comp++; if (maior > mx) mx = maior;                              // 1 com o maximo
    comp++; if (menor < mn) mn = menor;                              // 1 com o minimo
  }
}

// pesquisa sequencial: melhor caso 1, pior caso n, caso medio (n + 1) / 2 se a chave existe
long long custoSequencial(int v[], int n, int chave)
{
  long long comp = 0;
  for (int i = 0; i < n; i++) { comp++; if (v[i] == chave) break; }
  return comp;
}

int main()
{
  const int n = 1000;
  int v[n];
  srand(1);
  for (int i = 0; i < n; i++) v[i] = rand() % 100000;

  int mx, mn;
  long long comp;
  maxMinIngenuo(v, n, mx, mn, comp);
  cout << "Ingenuo: max = " << mx << ", min = " << mn << ", " << comp << " comparacoes (2(n-1) = " << 2 * (n - 1) << ")" << endl;
  maxMinPares(v, n, mx, mn, comp);
  cout << "Pares:   max = " << mx << ", min = " << mn << ", " << comp << " comparacoes (3n/2 - 2 = " << 3 * n / 2 - 2 << ")" << endl;

  long long soma = 0;
  for (int i = 0; i < n; i++) soma += custoSequencial(v, n, v[i]);
  cout << "\nPesquisa sequencial: melhor = " << custoSequencial(v, n, v[0])
       << ", pior = " << custoSequencial(v, n, -1)
       << ", medio = " << (double)soma / n << " ((n+1)/2 = " << (n + 1) / 2.0 << ")" << endl;
  return 0;
}
