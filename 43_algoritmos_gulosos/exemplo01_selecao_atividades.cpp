/*
Exemplo 1. Algoritmos gulosos: constroem a solucao com uma sequencia de escolhas, sempre a que parece
melhor no momento, sem voltar atras. Sao rapidos, mas so dao a resposta otima quando o problema tem
(1) propriedade da escolha gulosa e (2) subestrutura otima - e isso precisa ser provado.
Selecao de atividades: dadas atividades [inicio, fim), escolher o maior numero delas sem sobreposicao.
Escolha gulosa correta: a que TERMINA primeiro (deixa o maior tempo livre para as outras).
Outras escolhas que parecem boas (comecar primeiro, durar menos) podem falhar.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Atividade { string nome; int ini, fim; };

// aplica a regra gulosa: ordena pelo criterio e pega cada atividade compativel com as ja escolhidas
vector<Atividade> guloso(vector<Atividade> v, bool (*criterio)(const Atividade &, const Atividade &))
{
  sort(v.begin(), v.end(), criterio);
  vector<Atividade> escolhidas;
  for (const Atividade &a : v) {
    bool ok = true;
    for (const Atividade &e : escolhidas) if (a.ini < e.fim && e.ini < a.fim) ok = false;   // sobreposicao
    if (ok) escolhidas.push_back(a);
  }
  return escolhidas;
}

bool terminaAntes(const Atividade &a, const Atividade &b) { return a.fim < b.fim; }
bool comecaAntes(const Atividade &a, const Atividade &b) { return a.ini < b.ini; }
bool maisCurta(const Atividade &a, const Atividade &b) { return a.fim - a.ini < b.fim - b.ini; }

void mostra(const char *regra, const vector<Atividade> &r)
{
  cout << regra << ": " << r.size() << " atividades -> ";
  for (const Atividade &a : r) cout << a.nome << "[" << a.ini << "," << a.fim << ") ";
  cout << endl;
}

int main()
{
  vector<Atividade> v = {{"A", 1, 4}, {"B", 3, 5}, {"C", 0, 6}, {"D", 5, 7}, {"E", 3, 9}, {"F", 5, 9},
                         {"G", 6, 10}, {"H", 8, 11}, {"I", 8, 12}, {"J", 2, 14}, {"K", 12, 16}};
  mostra("Termina primeiro (otimo)", guloso(v, terminaAntes));
  mostra("Comeca primeiro         ", guloso(v, comecaAntes));

  vector<Atividade> w = {{"X", 0, 5}, {"Y", 4, 7}, {"Z", 6, 11}};   // a mais curta atrapalha as outras duas
  mostra("Mais curta (contraex.)  ", guloso(w, maisCurta));
  mostra("Termina primeiro        ", guloso(w, terminaAntes));
  return 0;
}
