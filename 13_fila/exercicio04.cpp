/*
Exercicio 4. Fila com prioridade simples: clientes preferenciais (p) sao atendidos antes dos normais (n). Usar duas filas.
*/
#include <iostream>
using namespace std;

// Fila dinamica: guarda ponteiro para o inicio e para o fim
struct No { int valor; No *prox; };
struct Fila { No *ini, *fim; };

void inicia(Fila &f) { f.ini = f.fim = nullptr; }
bool vazia(Fila &f) { return f.ini == nullptr; }

void enfileira(Fila &f, int x)
{
  No *n = new No; n->valor = x; n->prox = nullptr;
  if (vazia(f)) f.ini = n;   // primeiro elemento
  else f.fim->prox = n;      // liga no final
  f.fim = n;
}

bool desenfileira(Fila &f, int &x)
{
  if (vazia(f)) return false;
  No *aux = f.ini;
  x = aux->valor;
  f.ini = aux->prox;
  if (f.ini == nullptr) f.fim = nullptr;   // ficou vazia
  delete aux;
  return true;
}

int main()
{
  Fila pref, norm; inicia(pref); inicia(norm);
  int op, senha; char tipo;
  do {
    cout << "\n1-Chegou 2-Atender 0-Sair: "; cin >> op;
    if (op == 1) {
      cout << "Senha e tipo (p/n): "; cin >> senha >> tipo;
      if (tipo == 'p') enfileira(pref, senha); else enfileira(norm, senha);
    } else if (op == 2) {
      // sempre tenta a preferencial primeiro
      if (desenfileira(pref, senha)) cout << "Preferencial: " << senha << endl;
      else if (desenfileira(norm, senha)) cout << "Normal: " << senha << endl;
      else cout << "Filas vazias" << endl;
    }
  } while (op != 0);
  return 0;
}
