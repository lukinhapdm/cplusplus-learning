/*
Exemplo 1. Divisao e conquista: (1) dividir o problema em subproblemas menores do mesmo tipo,
(2) conquistar resolvendo-os recursivamente, (3) combinar as solucoes. Custo dado por recorrencia,
normalmente resolvida pelo Teorema Mestre (pasta 41).
Contagem de inversoes: pares (i, j) com i < j e v[i] > v[j] (mede o quanto um vetor esta "fora de ordem";
usado, por exemplo, para comparar rankings). Forca bruta O(n^2).
D&C: inversoes = as da metade esquerda + as da direita + as "cruzadas". As cruzadas sao contadas
durante a intercalacao do mergesort: quando um elemento da direita sai antes, ele forma inversao com
todos os que restam na esquerda. T(n) = 2T(n/2) + n = O(n log n).
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

long long ordenaConta(vector<int> &v, int ini, int fim, vector<int> &aux)   // intervalo [ini, fim)
{
  if (fim - ini <= 1) return 0;
  int meio = (ini + fim) / 2;
  long long inv = ordenaConta(v, ini, meio, aux) + ordenaConta(v, meio, fim, aux);   // conquista
  int i = ini, j = meio, k = ini;
  while (i < meio && j < fim) {   // combina (intercala) contando as cruzadas
    if (v[i] <= v[j]) aux[k++] = v[i++];
    else { aux[k++] = v[j++]; inv += meio - i; }   // v[j] e menor que todos os v[i..meio-1]
  }
  while (i < meio) aux[k++] = v[i++];
  while (j < fim) aux[k++] = v[j++];
  for (k = ini; k < fim; k++) v[k] = aux[k];
  return inv;
}

long long forcaBruta(const vector<int> &v)
{
  long long inv = 0;
  for (size_t i = 0; i < v.size(); i++)
    for (size_t j = i + 1; j < v.size(); j++) if (v[i] > v[j]) inv++;
  return inv;
}

int main()
{
  vector<int> v = {2, 4, 1, 3, 5};
  vector<int> aux(v.size());
  cout << "{2, 4, 1, 3, 5}: forca bruta = " << forcaBruta(v);
  cout << ", D&C = " << ordenaConta(v, 0, v.size(), aux) << "   (pares (2,1) (4,1) (4,3))" << endl;

  srand(5);
  vector<int> grande(20000);
  for (int &x : grande) x = rand();
  vector<int> copia = grande, aux2(grande.size());
  cout << "n = 20000: forca bruta = " << forcaBruta(copia) << ", D&C = " << ordenaConta(grande, 0, grande.size(), aux2) << endl;
  return 0;
}
