/*
Exercicio 3. Gravar uma arvore B em arquivo: cada pagina vira um registro de tamanho fixo e os ponteiros
viram numeros de pagina no arquivo (-1 = nulo). Depois buscar chaves lendo do arquivo apenas as paginas
do caminho (com seekg), contando os acessos a disco.
*/
#include <iostream>
#include <fstream>
using namespace std;

const int M = 2;
struct Pagina { int n = 0; int r[2 * M + 1]; Pagina *p[2 * M + 2] = {}; };

// formato no disco: sem ponteiros de memoria, so numeros de pagina
struct PaginaDisco { int n; int r[2 * M]; int filho[2 * M + 1]; };

bool ins(Pagina *ap, int k, int &kSobe, Pagina *&apSobe)
{
  int i = 0;
  while (i < ap->n && k > ap->r[i]) i++;
  if (i < ap->n && k == ap->r[i]) return false;
  Pagina *dir = nullptr;
  if (ap->p[0]) {
    if (!ins(ap->p[i], k, kSobe, apSobe)) return false;
    k = kSobe; dir = apSobe;
  }
  for (int j = ap->n; j > i; j--) { ap->r[j] = ap->r[j - 1]; ap->p[j + 1] = ap->p[j]; }
  ap->r[i] = k; ap->p[i + 1] = dir; ap->n++;
  if (ap->n <= 2 * M) return false;
  Pagina *nova = new Pagina;
  nova->n = M;
  for (int j = 0; j < M; j++) { nova->r[j] = ap->r[M + 1 + j]; nova->p[j] = ap->p[M + 1 + j]; }
  nova->p[M] = ap->p[2 * M + 1];
  for (int j = M + 1; j <= 2 * M + 1; j++) ap->p[j] = nullptr;
  kSobe = ap->r[M]; apSobe = nova; ap->n = M;
  return true;
}

void insere(Pagina *&raiz, int k)
{
  if (!raiz) { raiz = new Pagina; raiz->n = 1; raiz->r[0] = k; return; }
  int ks; Pagina *as;
  if (ins(raiz, k, ks, as)) { Pagina *r = new Pagina; r->n = 1; r->r[0] = ks; r->p[0] = raiz; r->p[1] = as; raiz = r; }
}

// grava em pos-ordem: os filhos antes do pai, para o pai ja saber o numero deles; devolve o numero da pagina
int grava(ofstream &f, Pagina *ap, int &proxNumero)
{
  if (!ap) return -1;
  PaginaDisco d;
  d.n = ap->n;
  for (int i = 0; i < 2 * M; i++) d.r[i] = i < ap->n ? ap->r[i] : 0;
  for (int i = 0; i <= 2 * M; i++) d.filho[i] = i <= ap->n ? grava(f, ap->p[i], proxNumero) : -1;
  f.write((char *)&d, sizeof(d));
  return proxNumero++;
}

bool buscaDisco(ifstream &f, int numRaiz, int k, int &acessos)
{
  int num = numRaiz;
  PaginaDisco d;
  while (num != -1) {
    f.seekg((long)num * sizeof(PaginaDisco));
    f.read((char *)&d, sizeof(d));
    acessos++;
    int i = 0;
    while (i < d.n && k > d.r[i]) i++;
    if (i < d.n && k == d.r[i]) return true;
    num = d.filho[i];
  }
  return false;
}

void libera(Pagina *ap) { if (ap) { for (int i = 0; i <= ap->n; i++) libera(ap->p[i]); delete ap; } }

int main()
{
  Pagina *raiz = nullptr;
  for (int k = 1; k <= 200; k++) insere(raiz, (k * 37) % 211);   // chaves embaralhadas

  int total = 0, numRaiz;
  {
    ofstream out("arvoreb.dat", ios::binary);
    numRaiz = grava(out, raiz, total);
  }
  cout << "Paginas gravadas: " << total << ", raiz na pagina " << numRaiz << endl;

  ifstream in("arvoreb.dat", ios::binary);
  for (int k : {37, 100, 210, 0}) {
    int acessos = 0;
    bool achou = buscaDisco(in, numRaiz, k, acessos);
    cout << "busca(" << k << "): " << (achou ? "achou" : "nao achou") << " com " << acessos << " acessos" << endl;
  }
  libera(raiz);
  return 0;
}
