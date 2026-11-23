/*
Exemplo 1. Ponteiros: endereco (&), conteudo (*) e passagem por ponteiro.
*/
#include <iostream>
using namespace std;

// recebe o endereco de a e b e troca o conteudo deles
void troca(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int x = 10, y = 20;
  int *p = &x;   // p guarda o endereco de x

  cout << "Endereco de x: " << p << endl;
  cout << "Valor apontado por p: " << *p << endl;
  *p = 15;       // altera x atraves do ponteiro
  cout << "x agora vale: " << x << endl;

  troca(&x, &y);
  cout << "Apos troca: x = " << x << ", y = " << y << endl;

  // alocacao dinamica: memoria criada em tempo de execucao
  int n = 3;
  int *v = new int[n];
  for (int i = 0; i < n; i++) v[i] = i * 10;
  for (int i = 0; i < n; i++) cout << *(v + i) << " ";   // aritmetica de ponteiros
  cout << endl;
  delete[] v;    // sempre liberar o que foi alocado com new
  return 0;
}
