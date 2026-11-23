/*
Exercício 3. Menu: sair, cadastrar, listar, conta(s) de maior saldo, de menor saldo, excluir conta.
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

// mostra todas as contas com o maior saldo (pode haver empate)
void maiorSaldo(Conta v[], int n)
{
  if (n == 0) return;
  float m = v[0].saldo;
  for (int i = 1; i < n; i++) if (v[i].saldo > m) m = v[i].saldo;
  for (int i = 0; i < n; i++) if (v[i].saldo == m) exibe(v[i]);
}

void menorSaldo(Conta v[], int n)
{
  if (n == 0) return;
  int p = 0;
  for (int i = 1; i < n; i++) if (v[i].saldo < v[p].saldo) p = i;
  exibe(v[p]);
}

// exclui puxando as contas seguintes uma posicao para tras
void exclui(Conta v[], int &n)
{
  int num;
  cout << "Numero da conta: "; cin >> num;
  int p = busca(v, n, num);
  if (p == -1) { cout << "Nao encontrada" << endl; return; }
  for (int i = p; i < n - 1; i++) v[i] = v[i + 1];
  n--;
  cout << "Conta excluida" << endl;
}

int main()
{
  Conta v[MAX_CONTAS];
  int n = 0, op;
  do {
    cout << "\n0-Sair 1-Cadastrar 2-Listar 3-Maior saldo 4-Menor saldo 5-Excluir: ";
    cin >> op;
    switch (op) {
      case 1: cadastra(v, n); break;
      case 2: lista(v, n); break;
      case 3: maiorSaldo(v, n); break;
      case 4: menorSaldo(v, n); break;
      case 5: exclui(v, n); break;
    }
  } while (op != 0);
  return 0;
}
