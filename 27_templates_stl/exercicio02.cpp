/*
Exercicio 2. Guardar alunos (nome, media) em um vector e usar sort com criterios diferentes:
(a) por media decrescente, desempate pelo nome; (b) por nome. Depois usar count_if para contar
os aprovados (media >= 6) e find_if para achar o primeiro reprovado.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Aluno { string nome; double media; };

// funcao de comparacao: retorna true se a deve vir antes de b
bool porMedia(const Aluno &a, const Aluno &b)
{
  if (a.media != b.media) return a.media > b.media;
  return a.nome < b.nome;
}

void lista(const vector<Aluno> &v)
{
  for (const Aluno &a : v) cout << "  " << a.nome << " " << a.media << endl;
}

int main()
{
  vector<Aluno> turma = {{"Carla", 7.5}, {"Bruno", 5.0}, {"Ana", 7.5}, {"Davi", 9.0}, {"Eva", 4.5}};

  sort(turma.begin(), turma.end(), porMedia);
  cout << "Por media:" << endl; lista(turma);

  // lambda: funcao anonima escrita no proprio ponto de uso
  sort(turma.begin(), turma.end(), [](const Aluno &a, const Aluno &b) { return a.nome < b.nome; });
  cout << "Por nome:" << endl; lista(turma);

  int aprovados = count_if(turma.begin(), turma.end(), [](const Aluno &a) { return a.media >= 6; });
  cout << "Aprovados: " << aprovados << endl;

  auto it = find_if(turma.begin(), turma.end(), [](const Aluno &a) { return a.media < 6; });
  if (it != turma.end()) cout << "Primeiro reprovado (ordem alfabetica): " << it->nome << endl;
  return 0;
}
