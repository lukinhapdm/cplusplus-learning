/*
Exercício 3. Ler nome do mês; abreviar para 3 letras + '.' em nova string; usar funções.
*/
#include <iostream>
#include <cstring>
using namespace std;

void leMes(char m[]) { cout << "Mes: "; cin >> m; }

// copia as 3 primeiras letras e coloca o ponto
void abrevia(const char m[], char ab[])
{
  strncpy(ab, m, 3);
  ab[3] = '.';
  ab[4] = '\0';   // fim da string
}

void mostra(const char ab[]) { cout << "Abreviacao: " << ab << endl; }

int main()
{
  char mes[20], ab[5];
  leMes(mes);
  abrevia(mes, ab);
  mostra(ab);
  return 0;
}
