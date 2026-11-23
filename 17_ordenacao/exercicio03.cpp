/*
Exercicio 3. Ordenar um vetor de structs Aluno (nome, nota) por nota decrescente usando Insertion Sort.
*/
#include <iostream>
#include <string>
using namespace std;

struct Aluno { string nome; float nota; };

void ordena(Aluno v[], int n)
{
  for (int i = 1; i < n; i++) {
    Aluno x = v[i]; int j = i - 1;
    while (j >= 0 && v[j].nota < x.nota) { v[j + 1] = v[j]; j--; }   // < para ficar decrescente
    v[j + 1] = x;
  }
}

int main()
{
  Aluno v[4] = {{"Ana", 7.5}, {"Bruno", 9.0}, {"Carla", 6.0}, {"Davi", 8.2}};
  ordena(v, 4);
  for (int i = 0; i < 4; i++) cout << v[i].nome << " - " << v[i].nota << endl;
  return 0;
}
