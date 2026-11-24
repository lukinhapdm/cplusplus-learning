/*
Exemplo 1. Sistemas de arquivos distribuidos (NFS, AFS...): os arquivos ficam num servidor e os clientes acessam
pela rede. Para nao ir ao servidor a cada leitura, o cliente guarda uma copia em CACHE; o problema passa a ser a
CONSISTENCIA dessa copia quando outro cliente altera o arquivo. Duas estrategias, simuladas com tempo logico:
  - validacao periodica (estilo NFS): a copia vale por um prazo (TTL); depois dele o cliente pergunta ao servidor
    a versao atual. Dentro do prazo pode ler dado velho;
  - callback (estilo AFS): o servidor lembra quem tem copia e AVISA (invalida) quando o arquivo muda.
    Leituras sempre atuais, ao custo de o servidor manter estado sobre os clientes.
*/
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

struct Arquivo { string conteudo; int versao; };

struct Servidor {
  map<string, Arquivo> arquivos;
  map<string, set<int>> callbacks;   // quem tem copia de cada arquivo (so no modo AFS)
  int acessos = 0;
};

struct Cliente {
  int id;
  bool afs;   // true: callback; false: TTL
  int ttl;
  map<string, Arquivo> cache;
  map<string, int> validoAte;
  map<string, bool> invalidado;

  string le(Servidor &s, const string &nome, int agora)
  {
    bool temCopia = cache.count(nome);
    bool precisaServidor = !temCopia || (afs ? invalidado[nome] : agora > validoAte[nome]);
    if (precisaServidor) {
      s.acessos++;
      cache[nome] = s.arquivos[nome];
      validoAte[nome] = agora + ttl;
      invalidado[nome] = false;
      if (afs) s.callbacks[nome].insert(id);
    }
    return cache[nome].conteudo + " (v" + to_string(cache[nome].versao) + (precisaServidor ? ", do servidor)" : ", da cache)");
  }

  void escreve(Servidor &s, const string &nome, const string &texto, map<int, Cliente *> &todos)
  {
    s.acessos++;
    Arquivo &a = s.arquivos[nome];
    a.conteudo = texto; a.versao++;
    cache[nome] = a;
    if (afs)   // servidor quebra o callback dos outros clientes
      for (int c : s.callbacks[nome]) if (c != id) todos[c]->invalidado[nome] = true;
  }
};

void simula(bool afs)
{
  cout << (afs ? "Callback (AFS):" : "Validacao por TTL = 5 (NFS):") << endl;
  Servidor s;
  s.arquivos["notas.txt"] = {"original", 1};
  Cliente a{1, afs, 5, {}, {}, {}}, b{2, afs, 5, {}, {}, {}};
  map<int, Cliente *> todos = {{1, &a}, {2, &b}};
  cout << "  t=0  A le: " << a.le(s, "notas.txt", 0) << endl;
  cout << "  t=1  B le: " << b.le(s, "notas.txt", 1) << endl;
  b.escreve(s, "notas.txt", "alterado por B", todos);
  cout << "  t=2  B escreve \"alterado por B\"" << endl;
  cout << "  t=3  A le: " << a.le(s, "notas.txt", 3) << endl;
  cout << "  t=7  A le: " << a.le(s, "notas.txt", 7) << endl;
  cout << "  acessos ao servidor: " << s.acessos << endl;
}

int main()
{
  simula(false);
  simula(true);
  return 0;
}
