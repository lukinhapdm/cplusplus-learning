#include <iostream>
using namespace std;

int main()
{
 float n1, n2, res;
 char op;
 cout << "Digite NUMERO OPERADOR NUMERO: ";
 cin >> n1 >> op >> n2;
 if (op == '+') { res = n1 + n2; cout << "O resultado da soma é: " << res; }
 else if (op == '-') { res = n1 - n2; cout << "O resultado da subtração é: " << res; }
 else if (op == '/') { res = n1 / n2; cout << "O resultado da divisão é: " << res; }
 else if (op == '*') { res = n1 * n2; cout << "O resultado da multiplicação é: " << res; }
 else cout << "Operador inválido!";
 cout << endl;
 return 0;
}
