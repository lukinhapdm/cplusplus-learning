/*
Exercicio 1. Para uma arvore B de ordem M, calcular: altura, numero de paginas, numero de chaves e
taxa de ocupacao (chaves / capacidade total). Inserir 1000 chaves aleatorias e comparar com
insercao em ordem crescente (que deixa as paginas so com M chaves, ocupacao perto de 50%).
*/
#include <iostream>
#include <cstdlib>
using namespace std;

const int M = 2;
struct Pagina { int n = 0; int r[2 * M + 1]; Pagina *p[2 * M + 2] = {}; };

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

int altura(Pagina *ap) { int h = 0; for (; ap; ap = ap->p[0]) h++; return h; }   // folhas no mesmo nivel

void conta(Pagina *ap, int &paginas, int &chaves)
{
  if (!ap) return;
  paginas++;
  chaves += ap->n;
  for (int i = 0; i <= ap->n; i++) conta(ap->p[i], paginas, chaves);
}

void libera(Pagina *ap) { if (ap) { for (int i = 0; i <= ap->n; i++) libera(ap->p[i]); delete ap; } }

void relatorio(const char *titulo, Pagina *raiz)
{
  int pag = 0, ch = 0;
  conta(raiz, pag, ch);
  cout << titulo << ": altura = " << altura(raiz) << ", paginas = " << pag << ", chaves = " << ch
       << ", ocupacao = " << 100.0 * ch / (pag * 2 * M) << "%" << endl;
}

int main()
{
  Pagina *a = nullptr, *b = nullptr;
  srand(1);
  for (int i = 0; i < 1000; i++) insere(a, rand() % 100000);
  for (int k = 1; k <= 1000; k++) insere(b, k);
  relatorio("Aleatoria", a);
  relatorio("Crescente", b);
  libera(a); libera(b);
  return 0;
}
