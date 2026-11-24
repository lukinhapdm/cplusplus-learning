/*
Exercicio 1. Eleicao de coordenador pelo algoritmo do valentao (bully). Processos 0..N-1; vence o de MAIOR id
que esteja ativo. Quando um processo percebe que o coordenador caiu:
  1) envia ELEICAO a todos os de id maior;
  2) se ninguem responder, ele vence e anuncia COORDENADOR a todos;
  3) se algum responder OK, ele desiste e espera; quem respondeu inicia a sua propria eleicao.
Simulacao deterministica (sem threads), contando as mensagens. Testar com diferentes processos falhos.
(Simplificacao: no algoritmo real todos os que responderam OK iniciam eleicoes ao mesmo tempo; aqui segue so o
menor deles, o que leva ao mesmo coordenador com menos mensagens.)
*/
#include <iostream>
#include <vector>
using namespace std;

int N, mensagens;
vector<bool> ativo;
int coordenador;

void eleicao(int p)
{
  cout << "  P" << p << " inicia eleicao" << endl;
  bool alguemMaior = false;
  for (int q = p + 1; q < N; q++) {
    mensagens++;   // ELEICAO p -> q
    if (ativo[q]) {
      mensagens++;   // OK q -> p
      cout << "    P" << q << " responde OK a P" << p << endl;
      alguemMaior = true;
    }
  }
  if (!alguemMaior) {
    coordenador = p;
    for (int q = 0; q < N; q++) if (q != p) mensagens++;   // COORDENADOR p -> todos
    cout << "  P" << p << " vence e anuncia que e o coordenador" << endl;
    return;
  }
  for (int q = p + 1; q < N; q++)   // os maiores ativos continuam; o primeiro deles que vencer encerra
    if (ativo[q]) { eleicao(q); return; }
}

void cenario(int n, vector<int> falhos, int detecta)
{
  N = n; mensagens = 0;
  ativo.assign(N, true);
  for (int f : falhos) ativo[f] = false;
  cout << "N = " << N << ", falhos:";
  for (int f : falhos) cout << " P" << f;
  cout << "; P" << detecta << " detecta a falha do coordenador" << endl;
  eleicao(detecta);
  cout << "Novo coordenador: P" << coordenador << " (" << mensagens << " mensagens)\n" << endl;
}

int main()
{
  cenario(6, {5}, 1);       // o antigo coordenador (5) caiu
  cenario(6, {5, 4}, 0);    // caiu tambem o 4: pior caso, quem detecta e o menor
  cenario(6, {5}, 4);       // quem detecta e o segundo maior: rapido
  return 0;
}
