/*
Exercicio 2. Hash de strings: agenda que guarda nome e telefone e busca o telefone pelo nome.
*/
#include <iostream>
#include <string>
using namespace std;

const int TAM = 13;
struct Contato { string nome, tel; Contato *prox; };

// soma os codigos das letras, ponderando pela posicao, e tira o resto
int h(string s)
{
  unsigned long v = 0;
  for (char c : s) v = v * 31 + c;
  return v % TAM;
}

void insere(Contato *t[], string nome, string tel)
{
  int p = h(nome);
  t[p] = new Contato{nome, tel, t[p]};
}

string busca(Contato *t[], string nome)
{
  for (Contato *a = t[h(nome)]; a; a = a->prox) if (a->nome == nome) return a->tel;
  return "nao encontrado";
}

int main()
{
  Contato *t[TAM] = {nullptr};
  insere(t, "Ana", "9999-1111");
  insere(t, "Bruno", "9888-2222");
  insere(t, "Carla", "9777-3333");
  string n;
  cout << "Nome para buscar: "; cin >> n;
  cout << "Telefone: " << busca(t, n) << endl;
  return 0;
}
