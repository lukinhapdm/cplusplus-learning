#include <iostream>
using namespace std;

void nao_muda(int a, double b) { a += 2; b += 5; } // por valor
void muda(int &a, double &b)   { a += 2; b += 5; } // por referência
int main()
{
 int n1 = 5; double n2 = 6.0;
 cout << "n1 = " << n1 << " n2 = " << n2 << endl;
 nao_muda(n1, n2);
 cout << "Valores apos a funcao nao_muda n1 = " << n1 << " n2 = " << n2 << endl;
 muda(n1, n2);
 cout << "Valores apos a funcao muda n1 = " << n1 << " n2 = " << n2 << endl;
 return 0;
}
