/*
Exercicio 2. Escolha da ordem: a altura maxima de uma arvore B de ordem M com n chaves e
h <= 1 + log_{M+1}((n + 1) / 2). Para n = 1.000.000, inserir as chaves em arvores com M = 2, 10, 50 e 100,
e mostrar a altura obtida, o limite teorico e quantas paginas uma busca le (a altura).
Conclusao: paginas grandes (M grande) deixam a arvore muito baixa, poucos acessos a disco.
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

struct Pagina {
  int n = 0;
  int *r;
  Pagina **p;
  Pagina(int M) : r(new int[2 * M + 1]), p(new Pagina *[2 * M + 2]()) {}   // () zera os ponteiros
  ~Pagina() { delete[] r; delete[] p; }
};

int M;   // ordem escolhida em tempo de execucao

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
  Pagina *nova = new Pagina(M);
  nova->n = M;
  for (int j = 0; j < M; j++) { nova->r[j] = ap->r[M + 1 + j]; nova->p[j] = ap->p[M + 1 + j]; }
  nova->p[M] = ap->p[2 * M + 1];
  for (int j = M + 1; j <= 2 * M + 1; j++) ap->p[j] = nullptr;
  kSobe = ap->r[M]; apSobe = nova; ap->n = M;
  return true;
}

void insere(Pagina *&raiz, int k)
{
  if (!raiz) { raiz = new Pagina(M); raiz->n = 1; raiz->r[0] = k; return; }
  int ks; Pagina *as;
  if (ins(raiz, k, ks, as)) { Pagina *r = new Pagina(M); r->n = 1; r->r[0] = ks; r->p[0] = raiz; r->p[1] = as; raiz = r; }
}

int altura(Pagina *ap) { int h = 0; for (; ap; ap = ap->p[0]) h++; return h; }
void libera(Pagina *ap) { if (ap) { for (int i = 0; i <= ap->n; i++) libera(ap->p[i]); delete ap; } }

int main()
{
  const int N = 1000000;
  int *chaves = new int[N];
  for (int i = 0; i < N; i++) chaves[i] = i;
  srand(2);
  for (int i = N - 1; i > 0; i--) { int j = (rand() * 32768LL + rand()) % (i + 1); int t = chaves[i]; chaves[i] = chaves[j]; chaves[j] = t; }   // embaralha

  for (int ordem : {2, 10, 50, 100}) {
    M = ordem;
    Pagina *raiz = nullptr;
    for (int i = 0; i < N; i++) insere(raiz, chaves[i]);
    double limite = 1 + log((N + 1) / 2.0) / log(M + 1.0);
    cout << "M = " << M << ": altura = " << altura(raiz) << " (limite " << limite << ")" << endl;
    libera(raiz);
  }
  delete[] chaves;
  return 0;
}
