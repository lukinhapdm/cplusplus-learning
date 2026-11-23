#include <iostream>
using namespace std;

int main()
{
 int dividendo, divisor;
 float quociente;
 cout << "Entre com o dividendo e o divisor, respectivamente: ";
 cin >> dividendo >> divisor;
 if (divisor != 0)
 {
  quociente = (float) dividendo / divisor;
  cout << "O quociente é: " << quociente << endl;
 }
 else
  cout << "Impossível fazer a divisão. O divisor é igual a zero." << endl;
 return 0;
}
