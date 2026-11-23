#include <iostream>
using namespace std;

int main()
{
  int x, n, i = 1, p = 17, d = 10;
  float t = 10, y = 2, xf = 3;
  x = 17 % 5;            // resto = 2
  x = -8; x = -x;        // 8
  x = x + 1; ++x; x++;   // incremento
  n = 5; x = ++n;        // pré-incremento
  cout << "n=" << n << " x=" << x << endl;
  n = 5; x = n++;        // pós-incremento
  cout << "n=" << n << " x=" << x << endl;
  i += 2; xf *= y + 1; t /= 2.5; p %= 5; d -= 3;
  float nota = 7.5; char sexo = 'f'; bool achou = false;
  cout << (nota >= 7.0 && nota < 8.0) << " " << (sexo=='f' || sexo=='m')
       << " " << !achou << " " << (n % 2 == 0) << endl;
  return 0;
}
