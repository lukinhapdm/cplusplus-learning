#include <iostream>
using namespace std;

int main(){
 int N, alunos = 1, acima_60 = 0;
 float nota, soma = 0, media;
 cout << "Digite a quantidade de alunos: "; cin >> N;
 while (alunos <= N){
  cout << "Digite a nota do aluno numero " << alunos << endl;
  cin >> nota;
  soma = soma + nota;
  if (nota > 60) acima_60++;
  alunos++;
 }
 media = soma / N;
 cout << "Número de alunos acima de 60: " << acima_60 << endl;
 cout << "Média das notas da turma: " << media;
 return 0;
}
