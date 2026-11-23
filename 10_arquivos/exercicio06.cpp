/*
Exercício 6. Programa modular: arquivo binário de filmes da locadora (gravar, buscar, excluir, listar).
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// em arquivo binario usamos char[] (tamanho fixo), nao string
struct Filme {
  int codigo;
  char titulo[60];
  char genero[20];
  int ano;
  bool disponivel;
};

const char ARQ[] = "filmes.dat";

// le todos os filmes do arquivo para o vetor; devolve a quantidade
int carrega(Filme v[], int max)
{
  ifstream in(ARQ, ios::binary);
  int n = 0;
  while (n < max && in.read((char*)&v[n], sizeof(Filme))) n++;
  return n;
}

// regrava o arquivo inteiro com o conteudo do vetor
void salvaTodos(Filme v[], int n)
{
  ofstream out(ARQ, ios::binary);
  out.write((char*)v, sizeof(Filme) * n);
}

void exibe(Filme f)
{
  cout << f.codigo << " | " << f.titulo << " | " << f.genero << " | " << f.ano
       << " | " << (f.disponivel ? "disponivel" : "alugado") << endl;
}

void inclui()
{
  Filme f;
  cout << "Codigo: "; cin >> f.codigo; cin.ignore();
  cout << "Titulo: "; cin.getline(f.titulo, 60);
  cout << "Genero: "; cin.getline(f.genero, 20);
  cout << "Ano: "; cin >> f.ano;
  f.disponivel = true;
  ofstream out(ARQ, ios::binary | ios::app);   // app: acrescenta no final
  out.write((char*)&f, sizeof(Filme));
}

void busca()
{
  Filme v[500]; int n = carrega(v, 500), cod;
  cout << "Codigo: "; cin >> cod;
  for (int i = 0; i < n; i++) if (v[i].codigo == cod) { exibe(v[i]); return; }
  cout << "Nao encontrado" << endl;
}

void exclui()
{
  Filme v[500]; int n = carrega(v, 500), cod, m = 0;
  cout << "Codigo: "; cin >> cod;
  // copia so os que NAO serao excluidos
  for (int i = 0; i < n; i++) if (v[i].codigo != cod) v[m++] = v[i];
  salvaTodos(v, m);
  cout << (m < n ? "Excluido" : "Nao encontrado") << endl;
}

void lista()
{
  Filme v[500]; int n = carrega(v, 500);
  for (int i = 0; i < n; i++) exibe(v[i]);
}

int main()
{
  int op;
  do {
    cout << "\n1-Incluir 2-Buscar 3-Excluir 4-Listar 0-Sair: ";
    cin >> op;
    switch (op) {
      case 1: inclui(); break;
      case 2: busca(); break;
      case 3: exclui(); break;
      case 4: lista(); break;
    }
  } while (op != 0);
  return 0;
}
