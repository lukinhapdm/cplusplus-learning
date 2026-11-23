#include <iostream>
using namespace std;

int maior(int vet[], int tam)
{
  int m = vet[0];
  for (int i = 1; i < tam; ++i) if (vet[i] > m) m = vet[i];
  return m;
}
int main()
{
  int valores[6] = {3, -1, 8, 12, 5, -6};
  cout << "Maior valor = " << maior(valores, 6) << endl;
}
