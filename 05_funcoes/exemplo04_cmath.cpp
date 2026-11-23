#include <iostream>
#include <cmath>
using namespace std;

int main()
{
 double base, expoente, numero;
 cout << "Digite a base: "; cin >> base;
 cout << "Digite o expoente: "; cin >> expoente; // (original tinha cout por engano)
 cout << "Potencia = " << pow(base, expoente) << endl;
 cout << "Digite um numero: "; cin >> numero;
 cout << "A raiz quadrada de " << numero << " e " << sqrt(numero) << endl;
 return 0;
}
