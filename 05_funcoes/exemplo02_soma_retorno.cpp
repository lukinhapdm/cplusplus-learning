#include <iostream>
using namespace std;

int soma(int n1, int n2)
{
 return n1 + n2;
}
int main()
{
 int numero1, numero2;
 cout << "Digite o primeiro numero: " << endl; cin >> numero1;
 cout << "Digite o segundo numero: " << endl; cin >> numero2;
 cout << "\n Soma = " << soma(numero1, numero2);
 return 0;
}
