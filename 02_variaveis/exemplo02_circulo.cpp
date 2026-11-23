#include <iostream>
using namespace std;

int main()
{
  const float pi=3.141592;
  float raio, area, comp;
  cout << "Cálculo da área de um círculo e do perímetro de sua circunferência." << endl;
  cout << "Por favor, entre com o raio: ";
  cin >> raio;
  area = pi * raio * raio;
  comp = 2 * pi * raio;
  cout << "A área do círculo é: " << area << endl;
  cout << "O comprimento de sua circunferência é: " << comp << endl;
  return 0;
}
