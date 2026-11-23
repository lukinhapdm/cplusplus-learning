/*
Exercicio 1. Simular uma fila de atendimento de banco: menu com 1-chegou cliente (le a senha), 2-atender proximo, 3-mostrar quantos esperam, 0-sair.
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

int tamanho(Fila &f)
{
  int c = 0;
  for (No *a = f.ini; a != nullptr; a = a->prox) c++;   // percorre contando
  return c;
}

int main()
{
  Fila f; inicia(f);
  int op, senha;
  do {
    cout << "\n1-Chegou 2-Atender 3-Esperando 0-Sair: "; cin >> op;
    if (op == 1) { cout << "Senha: "; cin >> senha; enfileira(f, senha); }
    else if (op == 2) {
      if (desenfileira(f, senha)) cout << "Atendendo senha " << senha << endl;
      else cout << "Ninguem na fila" << endl;
    }
    else if (op == 3) cout << tamanho(f) << " cliente(s) esperando" << endl;
  } while (op != 0);
  return 0;
}
