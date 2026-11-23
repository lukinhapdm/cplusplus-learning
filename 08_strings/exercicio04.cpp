/*
Exercício 4. Ler cidade natal e atual; verificar se são iguais; contar vogais da 2ª, trocar por '?' e mostrar.
*/
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool vogal(char c)
{
  c = tolower(c);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main()
{
  char natal[50], atual[50];
  cout << "Cidade natal: "; cin.getline(natal, 50);
  cout << "Cidade atual: "; cin.getline(atual, 50);
  if (strcmp(natal, atual) == 0) cout << "Mora na cidade natal" << endl;
  else cout << "Nao mora na cidade natal" << endl;
  int qtd = 0;
  for (int i = 0; atual[i] != '\0'; i++)
    if (vogal(atual[i])) { atual[i] = '?'; qtd++; }   // conta e troca
  cout << "Vogais: " << qtd << " | " << atual << endl;
  return 0;
}
