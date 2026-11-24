/*
Exemplo 3. Arvore B* (na nomenclatura de Ziviani; em outros livros e chamada de arvore B+).
- Todos os registros ficam nas folhas; as paginas internas guardam so chaves que servem de indice.
- Uma busca sempre vai ate a folha (mesmo que a chave apareca numa pagina interna).
- As folhas sao encadeadas, permitindo percorrer o arquivo em ordem (acesso sequencial) sem voltar a raiz.
Divisao de folha: a primeira chave da nova folha e COPIADA para o pai (continua na folha).
Divisao de pagina interna: a chave do meio SOBE para o pai (como na arvore B).
Obs.: Knuth usa "B*" para outra variante, em que as paginas ficam pelo menos 2/3 cheias porque, antes
de dividir, a pagina tenta redistribuir chaves com um irmao.
*/
#include <iostream>
using namespace std;

const int M = 2;

struct Pagina {
  bool folha = true;
  int n = 0;
  int r[2 * M + 1];                // uma posicao extra para o momento antes da divisao
  Pagina *p[2 * M + 2] = {};       // filhos (so paginas internas)
  Pagina *prox = nullptr;          // proxima folha (so folhas)
};

void insereEm(Pagina *ap, int i, int k, Pagina *dir)
{
  for (int j = ap->n; j > i; j--) { ap->r[j] = ap->r[j - 1]; ap->p[j + 1] = ap->p[j]; }
  ap->r[i] = k;
  ap->p[i + 1] = dir;
  ap->n++;
}

// devolve true se dividiu; nesse caso kSobe e nova devem ser inseridos no pai
bool ins(Pagina *ap, int k, int &kSobe, Pagina *&nova)
{
  int i = 0;
  if (ap->folha) {
    while (i < ap->n && ap->r[i] < k) i++;
    if (i < ap->n && ap->r[i] == k) return false;   // ja existe
    insereEm(ap, i, k, nullptr);
    if (ap->n <= 2 * M) return false;
    nova = new Pagina;                               // divide a folha: M ficam, M + 1 vao
    nova->n = M + 1;
    for (int j = 0; j <= M; j++) nova->r[j] = ap->r[M + j];
    ap->n = M;
    nova->prox = ap->prox;                           // mantem o encadeamento
    ap->prox = nova;
    kSobe = nova->r[0];                              // copia (nao sai da folha)
    return true;
  }
  while (i < ap->n && k >= ap->r[i]) i++;            // chave igual ao indice esta a direita
  int kFilho;
  Pagina *novoFilho;
  if (!ins(ap->p[i], k, kFilho, novoFilho)) return false;
  insereEm(ap, i, kFilho, novoFilho);
  if (ap->n <= 2 * M) return false;
  nova = new Pagina;                                 // divide pagina interna: a do meio sobe
  nova->folha = false;
  nova->n = M;
  for (int j = 0; j < M; j++) { nova->r[j] = ap->r[M + 1 + j]; nova->p[j] = ap->p[M + 1 + j]; }
  nova->p[M] = ap->p[2 * M + 1];
  kSobe = ap->r[M];
  ap->n = M;
  return true;
}

void insere(Pagina *&raiz, int k)
{
  if (!raiz) raiz = new Pagina;
  int kSobe;
  Pagina *nova;
  if (ins(raiz, k, kSobe, nova)) {
    Pagina *r = new Pagina;
    r->folha = false;
    r->n = 1; r->r[0] = kSobe; r->p[0] = raiz; r->p[1] = nova;
    raiz = r;
  }
}

Pagina *folhaDe(Pagina *ap, int k)   // desce ate a folha onde k esta (ou estaria)
{
  while (!ap->folha) {
    int i = 0;
    while (i < ap->n && k >= ap->r[i]) i++;
    ap = ap->p[i];
  }
  return ap;
}

bool busca(Pagina *raiz, int k)
{
  if (!raiz) return false;
  Pagina *f = folhaDe(raiz, k);
  for (int i = 0; i < f->n; i++) if (f->r[i] == k) return true;
  return false;
}

// chaves em [a, b]: desce uma vez e depois segue o encadeamento das folhas
void intervalo(Pagina *raiz, int a, int b)
{
  for (Pagina *f = folhaDe(raiz, a); f; f = f->prox)
    for (int i = 0; i < f->n; i++) {
      if (f->r[i] > b) return;
      if (f->r[i] >= a) cout << f->r[i] << " ";
    }
}

void imprime(Pagina *ap, int nivel = 0)
{
  for (int i = 0; i < nivel; i++) cout << "    ";
  cout << (ap->folha ? "folha [" : "indice [");
  for (int i = 0; i < ap->n; i++) cout << (i ? " " : "") << ap->r[i];
  cout << "]" << endl;
  if (!ap->folha) for (int i = 0; i <= ap->n; i++) imprime(ap->p[i], nivel + 1);
}

void libera(Pagina *ap) { if (!ap->folha) for (int i = 0; i <= ap->n; i++) libera(ap->p[i]); delete ap; }

int main()
{
  Pagina *raiz = nullptr;
  for (int k : {25, 10, 40, 5, 30, 15, 35, 20, 45, 50, 1, 12, 28, 33, 38, 42}) insere(raiz, k);
  imprime(raiz);
  cout << "busca(30) = " << busca(raiz, 30) << ", busca(31) = " << busca(raiz, 31) << endl;
  cout << "Chaves em [12, 38]: "; intervalo(raiz, 12, 38); cout << endl;
  cout << "Todas pelas folhas encadeadas: "; intervalo(raiz, -1000, 1000); cout << endl;
  libera(raiz);
  return 0;
}
