/*
Exercício 6. Inverter frase (string auxiliar), trocar vogais por '?'; função mostra qtd de cada vogal e a frase.
*/
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// conta cada vogal e mostra a frase final
void mostra(const char s[], int cont[5])
{
  const char v[] = "aeiou";
  for (int i = 0; i < 5; i++) cout << v[i] << ": " << cont[i] << endl;
  cout << "Frase final: " << s << endl;
}

int main()
{
  char frase[200], inv[200];
  int cont[5] = {0}, n;
  const char v[] = "aeiou";
  cout << "Frase: "; cin.getline(frase, 200);
  n = strlen(frase);
  // copia de tras para frente na string auxiliar
  for (int i = 0; i < n; i++) inv[i] = frase[n - 1 - i];
  inv[n] = '\0';
  // troca vogais por '?' e conta cada uma
  for (int i = 0; i < n; i++)
    for (int k = 0; k < 5; k++)
      if (tolower(inv[i]) == v[k]) { cont[k]++; inv[i] = '?'; }
  mostra(inv, cont);
  return 0;
}
