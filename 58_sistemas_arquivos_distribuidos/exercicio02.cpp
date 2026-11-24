/*
Exercicio 2. Armazenamento em blocos replicados (estilo HDFS / GFS): o arquivo e dividido em blocos de tamanho
fixo e cada bloco tem 3 replicas em nos diferentes; um servidor de nomes (NameNode) guarda onde esta cada bloco.
  1) gravar um arquivo de 10 blocos em 6 nos, escolhendo nos distintos para as replicas de cada bloco;
  2) derrubar nos e verificar se o arquivo ainda pode ser lido (todo bloco com pelo menos 1 replica viva);
  3) re-replicar: para cada bloco com menos de 3 replicas vivas, copiar para o no vivo MENOS carregado que
     ainda nao o tem (para nao concentrar tudo em poucos nos).
*/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
using namespace std;

const int NOS = 6, BLOCOS = 10, REPLICAS = 3;
vector<set<int>> local(BLOCOS);   // NameNode: bloco -> nos que tem copia
vector<bool> vivo(NOS, true);

int vivas(int b) { int c = 0; for (int n : local[b]) c += vivo[n]; return c; }

bool legivel()
{
  for (int b = 0; b < BLOCOS; b++) if (vivas(b) == 0) { cout << "  bloco " << b << " perdido!" << endl; return false; }
  return true;
}

void relatorio()
{
  for (int b = 0; b < BLOCOS; b++) {
    cout << "  bloco " << b << ":";
    for (int n : local[b]) cout << " N" << n << (vivo[n] ? "" : "(caiu)");
    cout << endl;
  }
}

int main()
{
  srand(4);
  for (int b = 0; b < BLOCOS; b++)
    while ((int)local[b].size() < REPLICAS) local[b].insert(rand() % NOS);   // set evita no repetido
  cout << "Distribuicao inicial:" << endl;
  relatorio();

  vivo[1] = vivo[4] = false;
  cout << "\nNos N1 e N4 cairam -> arquivo " << (legivel() ? "legivel" : "ILEGIVEL") << endl;

  for (int b = 0; b < BLOCOS; b++)   // o NameNode esquece as replicas dos nos mortos
    for (int n = 0; n < NOS; n++) if (!vivo[n]) local[b].erase(n);
  int copias = 0;
  for (int b = 0; b < BLOCOS; b++)
    while (vivas(b) < REPLICAS) {
      int melhor = -1, menorCarga = BLOCOS + 1;
      for (int n = 0; n < NOS; n++) {
        if (!vivo[n] || local[b].count(n)) continue;
        int carga = 0;
        for (int x = 0; x < BLOCOS; x++) carga += local[x].count(n);
        if (carga < menorCarga) { menorCarga = carga; melhor = n; }
      }
      if (melhor < 0) break;   // nao ha nos vivos suficientes
      local[b].insert(melhor);  // copia de uma replica viva para o no escolhido
      copias++;
    }
  cout << "Re-replicacao: " << copias << " copias feitas" << endl;
  relatorio();

  vivo[0] = vivo[2] = false;
  cout << "\nCairam tambem N0 e N2 -> arquivo " << (legivel() ? "legivel" : "ILEGIVEL")
       << endl;
  return 0;
}
