/*
Exemplo 1. Memoria secundaria (disco): grande e barata, porem muito mais lenta que a RAM. A unidade de
transferencia e o bloco (pagina): ler 1 byte custa o mesmo que ler o bloco inteiro. Por isso o custo
dos algoritmos em memoria secundaria e medido em numero de acessos a disco (paginas lidas).
Aqui um arquivo binario guarda registros de tamanho fixo, agrupados em paginas de REG_POR_PAG registros.
- Acesso sequencial: le pagina por pagina desde o inicio.
- Acesso direto: calcula a posicao (indice * sizeof(registro)) e pula com seekg.
*/
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

struct Registro { int chave; char nome[28]; };   // 32 bytes
const int REG_POR_PAG = 4;
const int N = 40;

void criaArquivo(const char *nomeArq)
{
  ofstream f(nomeArq, ios::binary);
  for (int i = 0; i < N; i++) {
    Registro r;
    r.chave = 10 * (i + 1);   // chaves 10, 20, ..., 400 (ordenadas)
    snprintf(r.nome, sizeof(r.nome), "item %d", i + 1);
    f.write((char *)&r, sizeof(r));
  }
}

// le uma pagina inteira; devolve quantos registros vieram
int lePagina(ifstream &f, int numPag, Registro pag[], int &acessos)
{
  f.clear();
  f.seekg((long)numPag * REG_POR_PAG * sizeof(Registro));
  f.read((char *)pag, REG_POR_PAG * sizeof(Registro));
  acessos++;
  return f.gcount() / sizeof(Registro);
}

bool buscaSequencial(ifstream &f, int chave, Registro &achado, int &acessos)
{
  Registro pag[REG_POR_PAG];
  for (int p = 0;; p++) {
    int qtd = lePagina(f, p, pag, acessos);
    if (qtd == 0) return false;   // fim do arquivo
    for (int i = 0; i < qtd; i++) if (pag[i].chave == chave) { achado = pag[i]; return true; }
  }
}

// acesso direto pelo numero do registro (posicao relativa)
bool leRegistro(ifstream &f, int indice, Registro &r, int &acessos)
{
  f.clear();
  f.seekg((long)indice * sizeof(Registro));
  acessos++;
  return (bool)f.read((char *)&r, sizeof(r));
}

int main()
{
  criaArquivo("registros.dat");
  ifstream f("registros.dat", ios::binary);
  Registro r;
  int acessos = 0;

  if (buscaSequencial(f, 370, r, acessos))
    cout << "Sequencial: " << r.chave << " - " << r.nome << " (" << acessos << " paginas lidas)" << endl;

  acessos = 0;
  if (leRegistro(f, 36, r, acessos))   // sabemos a posicao: um unico acesso
    cout << "Direto:     " << r.chave << " - " << r.nome << " (" << acessos << " acesso)" << endl;

  cout << "Tamanho do arquivo: " << N * sizeof(Registro) << " bytes, " << N / REG_POR_PAG << " paginas" << endl;
  return 0;
}
