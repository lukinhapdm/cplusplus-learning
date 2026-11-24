/*
Exemplo 1. Arvore B de ordem M: arvore de pesquisa balanceada feita para memoria secundaria.
Cada no (pagina) guarda varias chaves, entao a arvore fica baixa e cada busca le poucas paginas do disco.
Regras (ordem M):
  - cada pagina tem no maximo 2M chaves e 2M + 1 filhos;
  - toda pagina, exceto a raiz, tem no minimo M chaves;
  - todas as folhas estao no mesmo nivel (a arvore cresce pela raiz).
Insercao: desce ate a folha e insere em ordem. Se a pagina estourar (2M + 1 chaves), divide em duas de
M chaves e a chave do meio sobe para o pai (o que pode se propagar ate a raiz, criando uma nova raiz).
Aqui as paginas ficam em memoria; num sistema real cada Pagina seria um bloco do disco.
*/
#include <iostream>
using namespace std;

const int M = 2;

struct Pagina {
  int n = 0;                  // quantidade de chaves
  int r[2 * M];               // chaves em ordem
  Pagina *p[2 * M + 1] = {};  // p[i]: filho com chaves entre r[i-1] e r[i]
};

bool busca(Pagina *ap, int k, int &paginasLidas)
{
  while (ap) {
    paginasLidas++;
    int i = 0;
    while (i < ap->n && k > ap->r[i]) i++;   // pesquisa sequencial dentro da pagina
    if (i < ap->n && k == ap->r[i]) return true;
    ap = ap->p[i];
  }
  return false;
}

// insere a chave k (com o filho direito apDir) na posicao correta da pagina
void insereNaPagina(Pagina *ap, int k, Pagina *apDir)
{
  int i = ap->n;
  while (i > 0 && k < ap->r[i - 1]) {
    ap->r[i] = ap->r[i - 1];
    ap->p[i + 1] = ap->p[i];
    i--;
  }
  ap->r[i] = k;
  ap->p[i + 1] = apDir;
  ap->n++;
}

// cresceu = true quando a pagina abaixo dividiu e kSobe/apSobe precisam ser inseridos neste nivel
void ins(int k, Pagina *ap, bool &cresceu, int &kSobe, Pagina *&apSobe)
{
  if (!ap) { cresceu = true; kSobe = k; apSobe = nullptr; return; }   // chegou abaixo da folha

  int i = 0;
  while (i < ap->n && k > ap->r[i]) i++;
  if (i < ap->n && k == ap->r[i]) { cresceu = false; return; }        // ja existe

  ins(k, ap->p[i], cresceu, kSobe, apSobe);
  if (!cresceu) return;

  if (ap->n < 2 * M) {   // cabe na pagina
    insereNaPagina(ap, kSobe, apSobe);
    cresceu = false;
    return;
  }

  // pagina cheia: junta as 2M + 1 chaves, divide e a do meio sobe
  int chaves[2 * M + 1];
  Pagina *filhos[2 * M + 2];
  filhos[0] = ap->p[0];
  int j = 0, c = 0;
  bool usada = false;
  while (c < 2 * M + 1) {
    if (!usada && (j == ap->n || kSobe < ap->r[j])) { chaves[c] = kSobe; filhos[c + 1] = apSobe; usada = true; }
    else { chaves[c] = ap->r[j]; filhos[c + 1] = ap->p[j + 1]; j++; }
    c++;
  }
  Pagina *nova = new Pagina;
  ap->n = M;
  for (int t = 0; t < M; t++) { ap->r[t] = chaves[t]; ap->p[t + 1] = filhos[t + 1]; }
  ap->p[0] = filhos[0];
  for (int t = M + 1; t <= 2 * M; t++) ap->p[t] = nullptr;
  nova->n = M;
  nova->p[0] = filhos[M + 1];
  for (int t = 0; t < M; t++) { nova->r[t] = chaves[M + 1 + t]; nova->p[t + 1] = filhos[M + 2 + t]; }
  kSobe = chaves[M];   // chave do meio
  apSobe = nova;
  cresceu = true;
}

void insere(int k, Pagina *&raiz)
{
  bool cresceu;
  int kSobe;
  Pagina *apSobe;
  ins(k, raiz, cresceu, kSobe, apSobe);
  if (cresceu) {   // a raiz dividiu: arvore ganha um nivel
    Pagina *nova = new Pagina;
    nova->n = 1;
    nova->r[0] = kSobe;
    nova->p[0] = raiz;
    nova->p[1] = apSobe;
    raiz = nova;
  }
}

void imprime(Pagina *ap, int nivel = 0)
{
  if (!ap) return;
  for (int i = 0; i < nivel; i++) cout << "    ";
  cout << "[";
  for (int i = 0; i < ap->n; i++) cout << (i ? " " : "") << ap->r[i];
  cout << "]" << endl;
  for (int i = 0; i <= ap->n; i++) imprime(ap->p[i], nivel + 1);
}

void libera(Pagina *ap) { if (ap) { for (int i = 0; i <= ap->n; i++) libera(ap->p[i]); delete ap; } }

int main()
{
  Pagina *raiz = nullptr;
  int v[] = {20, 10, 40, 50, 30, 55, 3, 11, 4, 28, 36, 33, 52, 17, 25, 13, 45, 9, 43, 8, 48};
  for (int k : v) insere(k, raiz);
  imprime(raiz);
  for (int k : {45, 34}) {
    int lidas = 0;
    bool achou = busca(raiz, k, lidas);
    cout << "busca(" << k << "): " << (achou ? "achou" : "nao achou") << ", paginas lidas = " << lidas << endl;
  }
  libera(raiz);
  return 0;
}
