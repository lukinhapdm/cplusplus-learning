/*
Exercicio 2. Arquivo sequencial indexado: o arquivo esta ordenado e dividido em paginas; em memoria fica uma
tabela de indices com a primeira chave de cada pagina. Para buscar, procura na tabela (em memoria, sem custo
de disco) a pagina onde a chave pode estar e le apenas essa pagina: 1 acesso a disco por busca.
*/
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

struct Registro { int chave; char descricao[16]; };
const int ITENS_POR_PAGINA = 8;
const int N = 100;

int main()
{
  // cria o arquivo ordenado
  {
    ofstream out("indexado.dat", ios::binary);
    for (int i = 0; i < N; i++) {
      Registro r{5 * i + 2, ""};
      snprintf(r.descricao, sizeof(r.descricao), "prod%03d", i);
      out.write((char *)&r, sizeof(r));
    }
  }

  // monta a tabela de indices: primeira chave de cada pagina (uma leitura sequencial do arquivo)
  ifstream f("indexado.dat", ios::binary);
  int numPaginas = (N + ITENS_POR_PAGINA - 1) / ITENS_POR_PAGINA;
  int *tabela = new int[numPaginas];
  Registro pagina[ITENS_POR_PAGINA];
  for (int p = 0; p < numPaginas; p++) {
    f.read((char *)pagina, sizeof(pagina));
    tabela[p] = pagina[0].chave;
  }

  for (int chave : {2, 247, 400, 497, 1000}) {
    int p = 0;   // ultima pagina cuja primeira chave e <= chave procurada
    while (p + 1 < numPaginas && tabela[p + 1] <= chave) p++;
    f.clear();
    f.seekg((long)p * sizeof(pagina));
    f.read((char *)pagina, sizeof(pagina));   // unico acesso a disco
    int qtd = f.gcount() / sizeof(Registro);
    bool achou = false;
    for (int i = 0; i < qtd; i++)
      if (pagina[i].chave == chave) { cout << chave << ": " << pagina[i].descricao << " (pagina " << p << ")" << endl; achou = true; }
    if (!achou) cout << chave << ": nao encontrada (lida a pagina " << p << ")" << endl;
  }
  delete[] tabela;
  return 0;
}
