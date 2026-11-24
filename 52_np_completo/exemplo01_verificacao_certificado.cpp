/*
Exemplo 1. Classes de problemas (problemas de decisao: resposta sim/nao).
  - P: resolvidos em tempo polinomial (ex.: caminho minimo, ordenacao, arvore geradora minima).
  - NP: uma resposta "sim" tem um certificado que pode ser VERIFICADO em tempo polinomial
        (ex.: para SAT, uma atribuicao de valores que satisfaz a formula). P esta contido em NP.
  - NP-completo: esta em NP e todo problema de NP se reduz a ele em tempo polinomial
        (SAT foi o primeiro - teorema de Cook-Levin). Se algum NP-completo estiver em P, entao P = NP.
Aqui: SAT em forma normal conjuntiva (CNF). Verificar um certificado custa O(tamanho da formula);
encontrar um, sem ideia melhor, exige testar ate 2^n atribuicoes.
Literal positivo k = variavel x_k; negativo -k = nao x_k (variaveis de 1 a n).
*/
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> CNF;   // conjuncao (E) de clausulas; cada clausula e uma disjuncao (OU) de literais

bool verifica(const CNF &f, const vector<bool> &valor)   // polinomial: olha cada literal uma vez
{
  for (const auto &clausula : f) {
    bool satisfeita = false;
    for (int lit : clausula) if (lit > 0 ? valor[lit] : !valor[-lit]) { satisfeita = true; break; }
    if (!satisfeita) return false;
  }
  return true;
}

bool forcaBruta(const CNF &f, int n, vector<bool> &valor, long long &testadas)   // exponencial: 2^n
{
  testadas = 0;
  for (long long mask = 0; mask < (1LL << n); mask++) {
    testadas++;
    for (int k = 1; k <= n; k++) valor[k] = mask >> (k - 1) & 1;
    if (verifica(f, valor)) return true;
  }
  return false;
}

void mostra(const CNF &f)
{
  for (size_t c = 0; c < f.size(); c++) {
    cout << (c ? " E (" : "(");
    for (size_t i = 0; i < f[c].size(); i++) cout << (i ? " OU " : "") << (f[c][i] < 0 ? "~x" : "x") << abs(f[c][i]);
    cout << ")";
  }
  cout << endl;
}

int main()
{
  int n = 4;
  CNF f = {{1, -2, 3}, {-1, 2}, {2, -3, 4}, {-2, -4}, {-1, -3, -4}, {1, 4}};
  mostra(f);
  vector<bool> cert = {false, true, true, false, false};   // x1 = V, x2 = V, x3 = F, x4 = F (posicao 0 nao usada)
  cout << "Certificado x1=V x2=V x3=F x4=F: " << (verifica(f, cert) ? "valido" : "invalido") << endl;

  vector<bool> v(n + 1);
  long long t;
  if (forcaBruta(f, n, v, t)) {
    cout << "Forca bruta achou: ";
    for (int k = 1; k <= n; k++) cout << "x" << k << "=" << (v[k] ? "V " : "F ");
    cout << "(" << t << " atribuicoes testadas)" << endl;
  }
  CNF g = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}};   // insatisfazivel
  mostra(g);
  cout << (forcaBruta(g, 2, v, t) ? "satisfazivel" : "insatisfazivel") << " (" << t << " atribuicoes testadas = todas)" << endl;
  return 0;
}
