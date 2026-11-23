/*
7.1.4 Exercício 6. 20 valores + menu: 1-buscar posição, 2-alterar célula, 3-imprimir, 4-sair.
*/
#include <iostream>
using namespace std;

int main()
{
  int v[20], op, x, pos;
  cout << "Digite 20 valores: ";
  for (int i = 0; i < 20; i++) cin >> v[i];
  do {
    cout << "\n1. Buscar valor\n2. Alterar celula\n3. Imprimir\n4. Sair\nOpcao: ";
    cin >> op;
    if (op == 1) {
      cout << "Valor: "; cin >> x;
      bool achou = false;
      for (int i = 0; i < 20; i++)
        if (v[i] == x) { cout << "Esta na celula " << i << endl; achou = true; }
      if (!achou) cout << "Nao encontrado" << endl;
    } else if (op == 2) {
      cout << "Celula (0-19) e novo valor: "; cin >> pos >> x;
      if (pos >= 0 && pos < 20) v[pos] = x;
      else cout << "Celula invalida" << endl;
    } else if (op == 3) {
      for (int i = 0; i < 20; i++) cout << v[i] << " ";
      cout << endl;
    }
  } while (op != 4);
  return 0;
}
