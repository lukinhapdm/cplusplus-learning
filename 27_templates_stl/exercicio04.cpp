/*
Exercicio 4. Escrever um template de funcao pesquisaBinaria que funcione em qualquer container com
acesso aleatorio (vector, deque, array) recebendo iteradores [inicio, fim), e um template ordenaInsercao
que ordene o mesmo intervalo. Testar com vector<int> e deque<string>.
*/
#include <iostream>
#include <vector>
#include <deque>
#include <string>
using namespace std;

template <typename It, typename T>
It pesquisaBinaria(It inicio, It fim, const T &chave)
{
  It esq = inicio, dir = fim;   // intervalo [esq, dir)
  while (esq < dir) {
    It meio = esq + (dir - esq) / 2;
    if (*meio == chave) return meio;
    if (chave < *meio) dir = meio;
    else esq = meio + 1;
  }
  return fim;   // convencao da STL: "nao achou" = fim
}

template <typename It>
void ordenaInsercao(It inicio, It fim)
{
  for (It i = inicio + 1; i < fim; ++i) {
    auto x = *i;
    It j = i;
    while (j > inicio && x < *(j - 1)) { *j = *(j - 1); --j; }
    *j = x;
  }
}

int main()
{
  vector<int> v = {9, 4, 7, 1, 8, 2};
  ordenaInsercao(v.begin(), v.end());
  for (int x : v) cout << x << " ";
  auto it = pesquisaBinaria(v.begin(), v.end(), 7);
  cout << "\n7 na posicao " << (it - v.begin()) << endl;

  deque<string> d = {"uva", "pera", "abacaxi", "manga"};
  ordenaInsercao(d.begin(), d.end());
  for (auto &s : d) cout << s << " ";
  auto it2 = pesquisaBinaria(d.begin(), d.end(), string("kiwi"));
  cout << "\nkiwi " << (it2 == d.end() ? "nao encontrado" : "encontrado") << endl;
  return 0;
}
