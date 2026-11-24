/*
Exercicio 1. Pesquisa binaria em arquivo binario ordenado: usar seekg para ler so o registro do meio
a cada passo. Contar os acessos e comparar com a pesquisa sequencial no mesmo arquivo (1000 registros).
*/
#include <iostream>
#include <fstream>
using namespace std;

struct Registro { int chave; double valor; };
const int N = 1000;

bool leRegistro(fstream &f, int i, Registro &r, int &acessos)
{
  f.clear();
  f.seekg((long)i * sizeof(Registro));
  acessos++;
  return (bool)f.read((char *)&r, sizeof(r));
}

int binariaArquivo(fstream &f, int n, int chave, int &acessos)
{
  int esq = 0, dir = n - 1;
  Registro r;
  while (esq <= dir) {
    int meio = (esq + dir) / 2;
    leRegistro(f, meio, r, acessos);
    if (r.chave == chave) return meio;
    if (chave < r.chave) dir = meio - 1; else esq = meio + 1;
  }
  return -1;
}

int sequencialArquivo(fstream &f, int chave, int &acessos)
{
  f.clear();
  f.seekg(0);
  Registro r;
  for (int i = 0; f.read((char *)&r, sizeof(r)); i++) {
    acessos++;
    if (r.chave == chave) return i;
  }
  return -1;
}

int main()
{
  {
    ofstream out("ordenado.dat", ios::binary);
    for (int i = 0; i < N; i++) { Registro r{3 * i + 1, i * 1.5}; out.write((char *)&r, sizeof(r)); }
  }
  fstream f("ordenado.dat", ios::in | ios::binary);
  for (int chave : {1, 1501, 2998, 500}) {
    int ab = 0, as = 0;
    int pb = binariaArquivo(f, N, chave, ab);
    sequencialArquivo(f, chave, as);
    cout << "Chave " << chave << ": posicao " << pb << " | binaria " << ab << " acessos, sequencial " << as << " acessos" << endl;
  }
  return 0;
}
