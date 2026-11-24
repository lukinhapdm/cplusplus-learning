/*
Exemplo 1. Relogios logicos. Num sistema distribuido nao ha relogio global confiavel; o que importa e a ordem
causal dos eventos: a -> b ("aconteceu antes") se a e b sao do mesmo processo e a veio antes, ou se a e o
envio e b o recebimento da mesma mensagem (e transitividade). Se nem a -> b nem b -> a, sao CONCORRENTES.
- Relogio de Lamport (um inteiro por processo): incrementa a cada evento; a mensagem leva o valor e quem recebe
  faz L = max(L, L_msg) + 1. Garante: a -> b implica L(a) < L(b) (mas a reciproca nao vale).
- Relogio vetorial (um vetor de n inteiros): V[i]++ no proprio evento; ao receber, V = max(V, V_msg) posicao a
  posicao e depois V[i]++. Garante: a -> b se e somente se V(a) < V(b); detecta concorrencia.
Simulacao deterministica de 3 processos com um roteiro fixo de eventos.
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int N = 3;

struct Evento { int proc; char tipo; int outro; string nome; };   // tipo: 'l' local, 'e' envio, 'r' recebimento

struct Marca { int lamport; vector<int> vetor; };

bool antes(const vector<int> &a, const vector<int> &b)   // a < b: <= em tudo e diferente em algum
{
  bool menor = false;
  for (int i = 0; i < N; i++) { if (a[i] > b[i]) return false; if (a[i] < b[i]) menor = true; }
  return menor;
}

string mostra(const vector<int> &v)
{
  string s = "[";
  for (int i = 0; i < N; i++) s += (i ? "," : "") + to_string(v[i]);
  return s + "]";
}

int main()
{
  // roteiro: o recebimento de "m1" casa com o envio de mesmo nome
  vector<Evento> roteiro = {
    {0, 'l', -1, "a"}, {0, 'e', 1, "m1"}, {1, 'l', -1, "b"}, {2, 'l', -1, "c"}, {1, 'r', 0, "m1"},
    {1, 'e', 2, "m2"}, {2, 'e', 0, "m3"}, {0, 'r', 2, "m3"}, {2, 'r', 1, "m2"}, {0, 'l', -1, "d"}};

  vector<int> L(N, 0);
  vector<vector<int>> V(N, vector<int>(N, 0));
  map<string, Marca> mensagens, marcas;   // marca da mensagem em transito e marca de cada evento

  for (const Evento &e : roteiro) {
    int p = e.proc;
    if (e.tipo == 'r') {   // recebe: primeiro junta com a marca da mensagem
      Marca m = mensagens[e.nome];
      L[p] = max(L[p], m.lamport);
      for (int i = 0; i < N; i++) V[p][i] = max(V[p][i], m.vetor[i]);
    }
    L[p]++;
    V[p][p]++;
    string rotulo = (e.tipo == 'e' ? "envia " : e.tipo == 'r' ? "recebe " : "evento ") + e.nome;
    if (e.tipo == 'e') mensagens[e.nome] = {L[p], V[p]};   // a mensagem carrega o relogio
    string id = e.tipo == 'l' ? e.nome : e.nome + (e.tipo == 'e' ? ".env" : ".rec");
    marcas[id] = {L[p], V[p]};
    cout << "P" << p << " " << rotulo << ": Lamport = " << L[p] << ", vetorial = " << mostra(V[p]) << endl;
  }

  cout << "\nRelacoes entre eventos locais:" << endl;
  vector<string> evs = {"a", "b", "c", "d"};
  for (size_t i = 0; i < evs.size(); i++)
    for (size_t j = i + 1; j < evs.size(); j++) {
      Marca &x = marcas[evs[i]], &y = marcas[evs[j]];
      string rel = antes(x.vetor, y.vetor) ? " -> " : antes(y.vetor, x.vetor) ? " <- " : " || (concorrentes) ";
      cout << "  " << evs[i] << rel << evs[j] << "   (Lamport " << x.lamport << " e " << y.lamport << ")" << endl;
    }
  return 0;
}
