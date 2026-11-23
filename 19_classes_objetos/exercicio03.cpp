/*
Exercicio 3. Classe Turma que guarda um vetor dinamico de notas (tamanho no construtor), com metodos para adicionar nota, calcular media e destrutor liberando a memoria.
*/
#include <iostream>
using namespace std;

class Turma {
private:
  float *notas;
  int capacidade, qtd;
public:
  Turma(int cap) : capacidade(cap), qtd(0) { notas = new float[cap]; }
  ~Turma() { delete[] notas; }   // libera o que o construtor alocou
  Turma(const Turma &) = delete;            // proibe copia (ver exemplo03_construtor_copia)
  Turma &operator=(const Turma &) = delete;

  bool adiciona(float n) { if (qtd == capacidade) return false; notas[qtd++] = n; return true; }
  float media() const
  {
    if (qtd == 0) return 0;
    float s = 0;
    for (int i = 0; i < qtd; i++) s += notas[i];
    return s / qtd;
  }
};

int main()
{
  int n; float x;
  cout << "Quantos alunos? "; cin >> n;
  Turma t(n);
  for (int i = 0; i < n; i++) { cin >> x; t.adiciona(x); }
  cout << "Media: " << t.media() << endl;
  return 0;
}
