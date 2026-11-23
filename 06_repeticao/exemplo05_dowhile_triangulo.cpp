#include <iostream>
using namespace std;

int main(){
 float base, altura, area;
 do { cout << "Digite a medida da base: "; cin >> base; } while (base <= 0);
 do { cout << "\nDigite a medida da altura "; cin >> altura; } while (altura <= 0);
 area = base * altura / 2;
 cout << "Area = " << area;
 return 0;
}
