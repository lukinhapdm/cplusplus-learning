#include <iostream>
#include <string>
using namespace std;

struct Data { int dia, mes, ano; };
struct Funcionario { int codigo; string nome; float salario; char sexo; };
struct Venda { Data data; float valor; };

void cadastra(Funcionario &f) { cout << "Codigo, nome, salario, sexo: "; cin >> f.codigo >> f.nome >> f.salario >> f.sexo; }
void exibe(Funcionario f) { cout << f.codigo << " " << f.nome << " " << f.salario << " " << f.sexo << endl; }
Venda novaVenda(Data d, float v) { Venda x; x.data = d; x.valor = v; return x; }

int main()
{
  Funcionario f; cadastra(f); exibe(f);
  cout << "Inicial do nome: " << f.nome[0] << endl;
  Data d1 = {23, 11, 2026}, d2 = d1;           // inicialização e atribuição
  Venda v1 = novaVenda(d1, 100), v2 = novaVenda(d2, 50);
  cout << "Total: " << v1.valor + v2.valor << " em " << v1.data.dia << "/" << v1.data.mes << endl;
  return 0;
}
