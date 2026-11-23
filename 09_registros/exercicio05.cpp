/*
Exercício 5. 10 pacientes (nome, médico, nascimento, sexo): cadastrar, listar, listar ordenado asc/desc sem alterar original, excluir por nome, excluir todos de um médico.
*/
#include <iostream>
#include <string>
using namespace std;

struct Data { int dia, mes, ano; };

struct Paciente {
  string nome, medico;
  Data nasc;
  char sexo;
};

const int MAX = 10;

void cadastra(Paciente v[], int &n)
{
  if (n == MAX) { cout << "Lista cheia" << endl; return; }
  Paciente p;
  cout << "Nome, medico, dia mes ano, sexo: ";
  cin >> p.nome >> p.medico >> p.nasc.dia >> p.nasc.mes >> p.nasc.ano >> p.sexo;
  v[n++] = p;
}

void lista(Paciente v[], int n)
{
  for (int i = 0; i < n; i++)
    cout << v[i].nome << " | " << v[i].medico << " | " << v[i].nasc.dia << "/"
         << v[i].nasc.mes << "/" << v[i].nasc.ano << " | " << v[i].sexo << endl;
}

// ordena uma COPIA, assim a lista original nao muda
void listaOrdenada(Paciente v[], int n, bool crescente)
{
  Paciente c[MAX];
  for (int i = 0; i < n; i++) c[i] = v[i];
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++) {
      bool troca = crescente ? c[j].nome > c[j + 1].nome : c[j].nome < c[j + 1].nome;
      if (troca) { Paciente a = c[j]; c[j] = c[j + 1]; c[j + 1] = a; }
    }
  lista(c, n);
}

void removePos(Paciente v[], int &n, int p)
{
  for (int i = p; i < n - 1; i++) v[i] = v[i + 1];
  n--;
}

void excluiPaciente(Paciente v[], int &n)
{
  string nome; cout << "Nome do paciente: "; cin >> nome;
  for (int i = 0; i < n; i++)
    if (v[i].nome == nome) { removePos(v, n, i); cout << "Excluido" << endl; return; }
  cout << "Nao encontrado" << endl;
}

void excluiDoMedico(Paciente v[], int &n)
{
  string med; cout << "Nome do medico: "; cin >> med;
  for (int i = 0; i < n; )
    if (v[i].medico == med) removePos(v, n, i);   // nao avanca i: o proximo veio para ca
    else i++;
}

int main()
{
  Paciente v[MAX];
  int n = 0, op;
  do {
    cout << "\n1-Cadastrar 2-Listar 3-Ordem crescente 4-Ordem decrescente"
            " 5-Excluir paciente 6-Excluir do medico 0-Sair: ";
    cin >> op;
    switch (op) {
      case 1: cadastra(v, n); break;
      case 2: lista(v, n); break;
      case 3: listaOrdenada(v, n, true); break;
      case 4: listaOrdenada(v, n, false); break;
      case 5: excluiPaciente(v, n); break;
      case 6: excluiDoMedico(v, n); break;
    }
  } while (op != 0);
  return 0;
}
