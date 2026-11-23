/*
Exercicio 2. Classe Data (dia, mes, ano) que valida a data no construtor (incluindo ano bissexto) e tem metodo para imprimir no formato dd/mm/aaaa.
*/
#include <iostream>
#include <iomanip>
using namespace std;

class Data {
private:
  int dia, mes, ano;
  bool bissexto(int a) const { return (a % 4 == 0 && a % 100 != 0) || a % 400 == 0; }
  int diasNoMes(int m, int a) const
  {
    int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (m == 2 && bissexto(a)) ? 29 : d[m - 1];
  }
public:
  Data(int d, int m, int a)
  {
    // se a data for invalida, usa 01/01/2000
    if (m < 1 || m > 12 || d < 1 || d > diasNoMes(m, a)) { d = 1; m = 1; a = 2000; }
    dia = d; mes = m; ano = a;
  }
  void imprime() const
  {
    cout << setfill('0') << setw(2) << dia << "/" << setw(2) << mes << "/" << ano << endl;
  }
};

int main()
{
  Data d1(29, 2, 2024), d2(29, 2, 2023);
  d1.imprime();   // 29/02/2024
  d2.imprime();   // invalida -> 01/01/2000
  return 0;
}
