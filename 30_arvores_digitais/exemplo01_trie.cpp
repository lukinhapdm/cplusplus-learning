/*
Exemplo 1. Trie (arvore digital): a chave nao fica inteira em um no; cada nivel representa um caractere.
O caminho da raiz ate um no marcado como "fim" forma uma palavra. Para alfabeto a-z cada no tem 26 filhos.
Busca e insercao custam O(m), m = tamanho da chave, independente de quantas chaves existem.
Desvantagem: muitos ponteiros nulos (espaco).
*/
#include <iostream>
#include <string>
using namespace std;

const int ALFABETO = 26;

struct No {
  No *filho[ALFABETO] = {nullptr};
  bool fim = false;   // alguma palavra termina aqui?
};

class Trie {
  No *raiz = new No;

  void lista(No *n, string &prefixo)
  {
    if (n->fim) cout << prefixo << " ";
    for (int c = 0; c < ALFABETO; c++)   // percorre em ordem alfabetica
      if (n->filho[c]) {
        prefixo.push_back('a' + c);
        lista(n->filho[c], prefixo);
        prefixo.pop_back();
      }
  }

  bool semFilhos(No *n) { for (No *f : n->filho) if (f) return false; return true; }

  // remove recursivamente; devolve true se o no ficou inutil e pode ser apagado
  bool remove(No *n, const string &s, int i)
  {
    if (i == (int)s.size()) {
      if (!n->fim) return false;
      n->fim = false;
      return semFilhos(n);
    }
    No *&f = n->filho[s[i] - 'a'];
    if (!f) return false;
    if (remove(f, s, i + 1)) { delete f; f = nullptr; }
    return !n->fim && semFilhos(n);
  }

  void libera(No *n) { for (No *f : n->filho) if (f) libera(f); delete n; }

  No *desce(const string &s)
  {
    No *n = raiz;
    for (char ch : s) {
      n = n->filho[ch - 'a'];
      if (!n) return nullptr;
    }
    return n;
  }

public:
  ~Trie() { libera(raiz); }

  void insere(const string &s)
  {
    No *n = raiz;
    for (char ch : s) {
      int c = ch - 'a';
      if (!n->filho[c]) n->filho[c] = new No;   // cria o caminho se nao existir
      n = n->filho[c];
    }
    n->fim = true;
  }

  bool busca(const string &s) { No *n = desce(s); return n && n->fim; }
  bool temPrefixo(const string &p) { return desce(p) != nullptr; }
  void remove(const string &s) { remove(raiz, s, 0); }
  void lista() { string p; lista(raiz, p); cout << endl; }
};

int main()
{
  Trie t;
  string palavras[] = {"casa", "casamento", "caso", "cama", "carro", "dado", "dedo"};
  for (const string &p : palavras) t.insere(p);
  t.lista();
  cout << "busca(casa) = " << t.busca("casa") << ", busca(cas) = " << t.busca("cas")
       << ", prefixo(cas) = " << t.temPrefixo("cas") << endl;
  t.remove("casa");   // "casa" deixa de ser palavra, mas o caminho continua por causa de "casamento"
  t.remove("dedo");   // remove os nos "e", "d", "o" que so serviam a "dedo"
  t.lista();
  cout << "busca(casamento) = " << t.busca("casamento") << endl;
  return 0;
}
