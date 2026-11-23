/*
Exercício 2. Estender: cadastrar até 100 contas (MAX_CONTAS) com números únicos.
*/
#include <iostream>
#include <string>
using namespace std;

struct Conta {
  int numero;
  string cliente;
  float saldo;
};

const int MAX_CONTAS = 100;

// procura a conta pelo numero; devolve a posicao ou -1
int busca(Conta v[], int n, int num)
{
  for (int i = 0; i < n; i++) if (v[i].numero == num) return i;
  return -1;
}

// cadastra uma conta no final, sem repetir numero
void cadastra(Conta v[], int &n)
{
  if (n == MAX_CONTAS) { cout << "Limite atingido" << endl; return; }
  Conta c;
  cout << "Numero: "; cin >> c.numero;
  if (busca(v, n, c.numero) != -1) { cout << "Numero ja existe" << endl; return; }
  cout << "Cliente: "; cin.ignore(); getline(cin, c.cliente);
  cout << "Saldo: "; cin >> c.saldo;
  v[n++] = c;
}

void exibe(Conta c) { cout << c.numero << " | " << c.cliente << " | " << c.saldo << endl; }

void lista(Conta v[], int n) { for (int i = 0; i < n; i++) exibe(v[i]); }

int main()
{
  Conta v[MAX_CONTAS];
  int n = 0;        // quantas contas ja existem
  char resp = 's';
  while (resp == 's') {
    cadastra(v, n);
    cout << "Cadastrar outra? (s/n) "; cin >> resp;
  }
  lista(v, n);
  return 0;
}
