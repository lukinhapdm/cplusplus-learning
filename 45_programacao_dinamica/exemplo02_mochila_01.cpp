/*
Exemplo 2. Mochila 0/1: cada item entra inteiro ou nao entra; maximizar o valor com peso total <= W.
Subproblema: V[i][w] = melhor valor usando os i primeiros itens com capacidade w.
  V[0][w] = 0
  V[i][w] = V[i-1][w]                                   se peso[i] > w  (nao cabe)
          = max(V[i-1][w], V[i-1][w - peso[i]] + valor[i])  caso contrario (deixa ou leva)
A resposta e V[n][W]; os itens escolhidos sao recuperados voltando pela tabela.
Custo O(nW): pseudo-polinomial (depende do VALOR de W, nao do tamanho da entrada).
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
  vector<string> nome = {"", "notebook", "camera", "livros", "roupas", "garrafa"};
  vector<int> peso = {0, 4, 2, 3, 2, 1};
  vector<int> valor = {0, 40, 25, 20, 15, 8};
  int n = 5, W = 8;

  vector<vector<int>> V(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++)
    for (int w = 0; w <= W; w++) {
      V[i][w] = V[i - 1][w];                                            // nao leva o item i
      if (peso[i] <= w) V[i][w] = max(V[i][w], V[i - 1][w - peso[i]] + valor[i]);   // leva
    }

  printf("%-10s", "i \\ w");
  for (int w = 0; w <= W; w++) printf("%4d", w);
  printf("\n");
  for (int i = 0; i <= n; i++) {
    printf("%-10s", i ? nome[i].c_str() : "-");
    for (int w = 0; w <= W; w++) printf("%4d", V[i][w]);
    printf("\n");
  }

  cout << "Valor maximo: " << V[n][W] << "\nItens: ";
  for (int i = n, w = W; i > 0; i--)
    if (V[i][w] != V[i - 1][w]) {   // o valor mudou: o item i foi levado
      cout << nome[i] << " ";
      w -= peso[i];
    }
  cout << endl;
  return 0;
}
