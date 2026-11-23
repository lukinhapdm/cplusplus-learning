/*
Exercicio 4. Mostrar o problema de NAO usar destrutor virtual: classe derivada que aloca memoria e e apagada via ponteiro da base. Corrigir.
*/
#include <iostream>
using namespace std;

class BaseErrada {
public:
  ~BaseErrada() { cout << "~BaseErrada" << endl; }   // NAO virtual
};
class FilhaErrada : public BaseErrada {
  int *dados = new int[100];
public:
  ~FilhaErrada() { delete[] dados; cout << "~FilhaErrada (liberou memoria)" << endl; }
};

class BaseCerta {
public:
  virtual ~BaseCerta() { cout << "~BaseCerta" << endl; }   // virtual: resolve o problema
};
class FilhaCerta : public BaseCerta {
  int *dados = new int[100];
public:
  ~FilhaCerta() { delete[] dados; cout << "~FilhaCerta (liberou memoria)" << endl; }
};

int main()
{
  cout << "Sem virtual:" << endl;
  BaseErrada *e = new FilhaErrada;
  delete e;   // so chama ~BaseErrada -> vazamento de memoria
  cout << "Com virtual:" << endl;
  BaseCerta *c = new FilhaCerta;
  delete c;   // chama ~FilhaCerta e depois ~BaseCerta
  return 0;
}
