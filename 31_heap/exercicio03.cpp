/*
Exercicio 3. Intercalar k vetores ordenados em um so vetor ordenado usando um heap minimo
(priority_queue com greater) que guarda (valor, vetor de origem, posicao). Custo O(N log k).
*/
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main()
{
  vector<vector<int>> listas = {{1, 7, 15, 22}, {3, 4, 18}, {2, 9, 10, 11, 30}, {5}};
  typedef tuple<int, int, int> Item;   // (valor, lista, indice)
  priority_queue<Item, vector<Item>, greater<Item>> heap;

  for (int i = 0; i < (int)listas.size(); i++)
    if (!listas[i].empty()) heap.push(Item(listas[i][0], i, 0));   // o primeiro de cada lista

  vector<int> resultado;
  while (!heap.empty()) {
    int valor, l, j;
    tie(valor, l, j) = heap.top(); heap.pop();
    resultado.push_back(valor);
    if (j + 1 < (int)listas[l].size()) heap.push(Item(listas[l][j + 1], l, j + 1));   // proximo da mesma lista
  }
  for (int x : resultado) cout << x << " ";
  cout << endl;
  return 0;
}
