#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Funcionario { int codigo; char nome[40]; float salario; };

int main()
{
  // texto: escrita e leitura linha a linha
  ofstream out("teste.txt"); out << "Linha 1\nLinha 2\n"; out.close();
  ifstream in("teste.txt"); string linha;
  while (getline(in, linha)) cout << linha << endl;
  in.close();

  // binário: vetor de registros com contador no cabeçalho
  Funcionario v[2] = {{1, "Ana", 3000}, {2, "Bruno", 2500}};
  int n = 2;
  ofstream ob("func.dat", ios::binary);
  ob.write((char*)&n, sizeof(n)); ob.write((char*)v, sizeof(Funcionario) * n); ob.close();

  Funcionario r[10]; int m;
  ifstream ib("func.dat", ios::binary);
  ib.read((char*)&m, sizeof(m)); ib.read((char*)r, sizeof(Funcionario) * m); ib.close();
  for (int i = 0; i < m; i++) cout << r[i].codigo << " " << r[i].nome << " " << r[i].salario << endl;
  return 0;
}
