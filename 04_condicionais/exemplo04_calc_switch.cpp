#include <iostream>
using namespace std;

int main()
{
 float n1, n2, res;
 char op;
 cout << "Digite NUMERO OPERADOR NUMERO: ";
 cin >> n1 >> op >> n2;
 switch (op)
 {
  case '+': res = n1 + n2; cout << "O resultado da soma é: " << res; break;
  case '-': res = n1 - n2; cout << "O resultado da subtração é: " << res; break;
  case '\\':
  case '/': res = n1 / n2; cout << "O resultado da divisão é: " << res; break;
  case 'x':
  case '*': res = n1 * n2; cout << "O resultado da multiplicação é: " << res; break;
  default: cout << "Operador inválido!";
 }
 cout << endl;
 return 0;
}
