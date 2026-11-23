/*
Exercício 4. Registros Professor e Título: cadastrar 5 títulos, 10 professores (título existente), listar em tabela.
*/
#include <iostream>
#include <string>
using namespace std;

struct Titulo {
  int codigo;
  string descricao;
  float valorHora;
};

struct Professor {
  int registro;
  string nome;
  int codTitulo;
  int horas;   // horas semanais
};

// devolve a posicao do titulo com esse codigo, ou -1
int buscaTitulo(Titulo t[], int n, int cod)
{
  for (int i = 0; i < n; i++) if (t[i].codigo == cod) return i;
  return -1;
}

void cadastraTitulos(Titulo t[])
{
  for (int i = 0; i < 5; i++) {
    cout << "Titulo " << i + 1 << " (codigo, descricao, valor hora): ";
    cin >> t[i].codigo >> t[i].descricao >> t[i].valorHora;
  }
}

void cadastraProfessores(Professor p[], Titulo t[])
{
  for (int i = 0; i < 10; i++) {
    cout << "Professor " << i + 1 << " (registro, nome, horas): ";
    cin >> p[i].registro >> p[i].nome >> p[i].horas;
    // so aceita titulo ja cadastrado
    do { cout << "Codigo do titulo: "; cin >> p[i].codTitulo; }
    while (buscaTitulo(t, 5, p[i].codTitulo) == -1);
  }
}

void listaProfessores(Professor p[], Titulo t[])
{
  cout << "Registro | Nome | Titulo | Horas | Valor hora" << endl;
  for (int i = 0; i < 10; i++) {
    Titulo ti = t[buscaTitulo(t, 5, p[i].codTitulo)];
    cout << p[i].registro << " | " << p[i].nome << " | " << ti.descricao
         << " | " << p[i].horas << " | " << ti.valorHora << endl;
  }
}

int main()
{
  Titulo t[5];
  Professor p[10];
  cadastraTitulos(t);
  cadastraProfessores(p, t);
  listaProfessores(p, t);
  return 0;
}
