#include <iostream>
using namespace std;

void soma(); // protótipo
int main()
{
 soma();
 return 0;
}
void soma()
{
 int n1, n2, s;
 cout << "Digite o primeiro numero: " << endl; cin >> n1;
 cout << "Digite o segundo numero: " << endl; cin >> n2;
 s = n1 + n2;
 cout << "\n Soma = " << s;
}
