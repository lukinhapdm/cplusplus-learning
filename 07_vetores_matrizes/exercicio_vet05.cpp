/*
7.1.4 Exercício 5. Temperaturas de N dias: média e desvio padrão sqrt(sum((vi-m)^2)/(N-1)).
*/
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  int n;
  float soma = 0, m, s = 0;
  cout << "Numero de dias N: "; cin >> n;
  float t[n];
  for (int i = 0; i < n; i++) { cout << "Temperatura dia " << i + 1 << ": "; cin >> t[i]; soma += t[i]; }
  m = soma / n;                                   // media
  for (int i = 0; i < n; i++) s += (t[i] - m) * (t[i] - m);   // soma dos quadrados das diferencas
  cout << "Media: " << m << endl;
  if (n > 1) cout << "Desvio padrao: " << sqrt(s / (n - 1)) << endl;
  return 0;
}
