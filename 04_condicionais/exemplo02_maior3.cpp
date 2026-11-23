#include <iostream>
using namespace std;

int main()
{
 int n1, n2, n3;
 cout << "Entre com 3 numeros inteiros: ";
 cin >> n1 >> n2 >> n3;
 if (n1 > n2)
 {
  if (n1 > n3) cout << "O maior é: " << n1;
  else cout << "O maior é: " << n3;
 }
 else
 {
  if (n2 > n3) cout << "O maior é: " << n2;
  else cout << "O maior é: " << n3;
 }
 return 0;
}
