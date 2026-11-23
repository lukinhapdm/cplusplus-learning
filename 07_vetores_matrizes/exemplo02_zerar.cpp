#include <iostream>
using namespace std;

void zerar(int vet[], int tam) { for (int i = 0; i < tam; ++i) vet[i] = 0; }
int main()
{
  int v[4] = {10, 20, 30, 40};
  cout << "v = [" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "]" << endl;
  zerar(v, 4);
  cout << "v = [" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "]" << endl;
}
