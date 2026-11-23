#include <iostream>
#include <cstring>
using namespace std;

int contaH(const char s[]) { int c = 0, n = strlen(s); for (int i = 0; i < n; i++) if (s[i]=='h') c++; return c; }
int main()
{
  char a[] = "UNIFEI", b[20] = {'U','N','I','F','E','I','\0'}, c[40], nome[80];
  cout << "Tamanho: " << strlen(a) << endl;          // strlen
  strcpy(c, a); strcat(c, " - Itajuba");            // strcpy / strcat
  cout << c << endl;
  cout << "Digite UNIFEI: "; cin.getline(nome, 80); // (gets é obsoleto)
  if (strcmp(nome, b) == 0) cout << "Iguais" << endl; // strcmp
  for (int i = 0; nome[i] != '\0'; i++) cout << nome[i] << endl;
  cout << "Qtd de 'h': " << contaH(nome) << endl;
  return 0;
}
