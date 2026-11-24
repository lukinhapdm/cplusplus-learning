/*
Exemplo 2. Remocao em arvore B de ordem M.
1) Se a chave esta em pagina interna, troca pela antecessora (maior chave da subarvore esquerda),
   que esta sempre em uma folha, e remove a antecessora da folha.
2) Se uma pagina fica com menos de M chaves (underflow), o pai corrige:
   - emprestimo: se um irmao vizinho tem mais de M chaves, a chave do pai desce para a pagina
     e a chave extrema do irmao sobe para o pai (uma rotacao);
   - juncao: senao, junta a pagina, a chave do pai que separa as duas e o irmao numa unica pagina
     (o pai perde uma chave e pode entrar em underflow, propagando ate a raiz).
3) Se a raiz fica vazia, seu unico filho vira a nova raiz (a arvore diminui um nivel).
*/
#include <iostream>
using namespace std;

const int M = 2;
struct Pagina { int n = 0; int r[2 * M + 1]; Pagina *p[2 * M + 2] = {}; };   // uma posicao extra para facilitar

// ---------- insercao (versao compacta: insere e divide se passar de 2M) ----------
void ins(Pagina *ap, int k, bool &dividiu, int &kSobe, Pagina *&apSobe)
{
  int i = 0;
  while (i < ap->n && k > ap->r[i]) i++;
  if (i < ap->n && k == ap->r[i]) { dividiu = false; return; }
  Pagina *dir = nullptr;
  if (ap->p[0]) {   // interna: desce
    ins(ap->p[i], k, dividiu, kSobe, apSobe);
    if (!dividiu) return;
    k = kSobe; dir = apSobe;
  }
  for (int j = ap->n; j > i; j--) { ap->r[j] = ap->r[j - 1]; ap->p[j + 1] = ap->p[j]; }
  ap->r[i] = k; ap->p[i + 1] = dir; ap->n++;
  dividiu = ap->n > 2 * M;
  if (!dividiu) return;
  Pagina *nova = new Pagina;   // divide: M chaves ficam, a do meio sobe, M vao para a nova
  nova->n = M;
  for (int j = 0; j < M; j++) { nova->r[j] = ap->r[M + 1 + j]; nova->p[j] = ap->p[M + 1 + j]; }
  nova->p[M] = ap->p[2 * M + 1];
  for (int j = M + 1; j <= 2 * M + 1; j++) ap->p[j] = nullptr;
  kSobe = ap->r[M]; apSobe = nova; ap->n = M;
}

void insere(Pagina *&raiz, int k)
{
  if (!raiz) { raiz = new Pagina; raiz->n = 1; raiz->r[0] = k; return; }
  bool d; int ks; Pagina *as;
  ins(raiz, k, d, ks, as);
  if (d) { Pagina *nr = new Pagina; nr->n = 1; nr->r[0] = ks; nr->p[0] = raiz; nr->p[1] = as; raiz = nr; }
}

// ---------- remocao ----------
void removeDaPagina(Pagina *ap, int i)   // tira r[i] e p[i+1]
{
  for (int j = i; j < ap->n - 1; j++) { ap->r[j] = ap->r[j + 1]; ap->p[j + 1] = ap->p[j + 2]; }
  ap->p[ap->n] = nullptr;
  ap->n--;
}

// o filho p[i] de pai ficou com menos de M chaves
void corrige(Pagina *pai, int i)
{
  Pagina *c = pai->p[i];
  Pagina *esq = i > 0 ? pai->p[i - 1] : nullptr;
  Pagina *dir = i < pai->n ? pai->p[i + 1] : nullptr;

  if (esq && esq->n > M) {   // emprestimo do irmao esquerdo
    for (int j = c->n; j > 0; j--) c->r[j] = c->r[j - 1];
    for (int j = c->n + 1; j > 0; j--) c->p[j] = c->p[j - 1];
    c->r[0] = pai->r[i - 1];
    c->p[0] = esq->p[esq->n];
    c->n++;
    pai->r[i - 1] = esq->r[esq->n - 1];
    esq->p[esq->n] = nullptr;
    esq->n--;
    return;
  }
  if (dir && dir->n > M) {   // emprestimo do irmao direito
    c->r[c->n] = pai->r[i];
    c->p[c->n + 1] = dir->p[0];
    c->n++;
    pai->r[i] = dir->r[0];
    for (int j = 0; j < dir->n - 1; j++) dir->r[j] = dir->r[j + 1];
    for (int j = 0; j < dir->n; j++) dir->p[j] = dir->p[j + 1];
    dir->p[dir->n] = nullptr;
    dir->n--;
    return;
  }
  // juncao: une p[j], r[j] e p[j+1]
  int j = esq ? i - 1 : i;
  Pagina *a = pai->p[j], *b = pai->p[j + 1];
  a->r[a->n] = pai->r[j];
  for (int t = 0; t < b->n; t++) { a->r[a->n + 1 + t] = b->r[t]; a->p[a->n + 1 + t] = b->p[t]; }
  a->p[a->n + 1 + b->n] = b->p[b->n];
  a->n += 1 + b->n;
  delete b;
  removeDaPagina(pai, j);
}

// remove e devolve a maior chave da subarvore (sempre em uma folha)
int removeMaior(Pagina *ap)
{
  if (!ap->p[0]) { ap->n--; return ap->r[ap->n]; }
  int k = removeMaior(ap->p[ap->n]);
  if (ap->p[ap->n]->n < M) corrige(ap, ap->n);
  return k;
}

void rem(Pagina *ap, int k)
{
  int i = 0;
  while (i < ap->n && k > ap->r[i]) i++;
  bool achou = i < ap->n && k == ap->r[i];
  if (!ap->p[0]) {   // folha
    if (achou) removeDaPagina(ap, i);
    return;
  }
  if (achou) ap->r[i] = removeMaior(ap->p[i]);   // troca pela antecessora
  else rem(ap->p[i], k);
  if (ap->p[i]->n < M) corrige(ap, i);
}

void remove(Pagina *&raiz, int k)
{
  if (!raiz) return;
  rem(raiz, k);
  if (raiz->n == 0) {   // raiz vazia: o filho sobe (ou a arvore fica vazia)
    Pagina *velha = raiz;
    raiz = raiz->p[0];
    delete velha;
  }
}

void imprime(Pagina *ap, int nivel = 0)
{
  if (!ap) return;
  for (int i = 0; i < nivel; i++) cout << "    ";
  cout << "[";
  for (int i = 0; i < ap->n; i++) cout << (i ? " " : "") << ap->r[i];
  cout << "]" << endl;
  if (ap->p[0]) for (int i = 0; i <= ap->n; i++) imprime(ap->p[i], nivel + 1);
}

void libera(Pagina *ap) { if (ap) { if (ap->p[0]) for (int i = 0; i <= ap->n; i++) libera(ap->p[i]); delete ap; } }

int main()
{
  Pagina *raiz = nullptr;
  for (int k = 1; k <= 20; k++) insere(raiz, k);
  cout << "Inicial:" << endl; imprime(raiz);
  remove(raiz, 12);   // esta em pagina interna: troca pela antecessora
  cout << "\nApos remover 12:" << endl; imprime(raiz);
  remove(raiz, 1); remove(raiz, 2);   // folha fica com 1 chave: emprestimo ou juncao
  cout << "\nApos remover 1 e 2:" << endl; imprime(raiz);
  for (int k = 3; k <= 15; k++) remove(raiz, k);   // forca juncoes ate a raiz diminuir
  cout << "\nApos remover 3..15:" << endl; imprime(raiz);
  libera(raiz);
  return 0;
}
