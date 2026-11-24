/*
Exemplo 2. Enderecamento aberto com tres estrategias de sondagem e remocao logica.
- Linear:     h(k, i) = (h1(k) + i) mod M
- Quadratica: h(k, i) = (h1(k) + i*i) mod M
- Dupla:      h(k, i) = (h1(k) + i*h2(k)) mod M, com h2(k) nunca zero
Na remocao a posicao e marcada como REMOVIDO (e nao VAZIO), senao a busca de chaves que colidiram
pararia antes da hora.
*/
#include <iostream>
using namespace std;

const int M = 11;
const int VAZIO = -1, REMOVIDO = -2;
enum Sondagem { LINEAR, QUADRATICA, DUPLA };

class TabelaHash {
  int t[M];
  Sondagem tipo;
  int h1(int k) { return k % M; }
  int h2(int k) { return 1 + k % (M - 1); }   // 1..M-1, nunca zero
  int pos(int k, int i)
  {
    if (tipo == LINEAR) return (h1(k) + i) % M;
    if (tipo == QUADRATICA) return (h1(k) + i * i) % M;
    return (h1(k) + i * h2(k)) % M;
  }
public:
  int colisoes = 0;
  TabelaHash(Sondagem s) : tipo(s) { for (int i = 0; i < M; i++) t[i] = VAZIO; }

  bool insere(int k)
  {
    for (int i = 0; i < M; i++) {
      int p = pos(k, i);
      if (t[p] == VAZIO || t[p] == REMOVIDO) { t[p] = k; return true; }
      colisoes++;
    }
    return false;   // nao achou posicao livre
  }

  int busca(int k)
  {
    for (int i = 0; i < M; i++) {
      int p = pos(k, i);
      if (t[p] == VAZIO) return -1;   // REMOVIDO nao interrompe a busca
      if (t[p] == k) return p;
    }
    return -1;
  }

  bool remove(int k)
  {
    int p = busca(k);
    if (p == -1) return false;
    t[p] = REMOVIDO;   // remocao logica
    return true;
  }

  void imprime()
  {
    for (int i = 0; i < M; i++) {
      if (t[i] == VAZIO) cout << "- ";
      else if (t[i] == REMOVIDO) cout << "R ";
      else cout << t[i] << " ";
    }
    cout << "(colisoes: " << colisoes << ")" << endl;
  }
};

int main()
{
  int chaves[] = {22, 33, 44, 55, 15, 26, 4};   // varias caem na posicao 0 ou 4
  TabelaHash lin(LINEAR), quad(QUADRATICA), dupla(DUPLA);
  for (int k : chaves) { lin.insere(k); quad.insere(k); dupla.insere(k); }
  cout << "Linear:     "; lin.imprime();
  cout << "Quadratica: "; quad.imprime();
  cout << "Dupla:      "; dupla.imprime();

  lin.remove(33);
  cout << "\nLinear apos remover 33: "; lin.imprime();
  cout << "44 ainda e encontrado na posicao " << lin.busca(44) << endl;
  return 0;
}
