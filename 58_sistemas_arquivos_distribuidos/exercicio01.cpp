/*
Exercicio 1. Semanticas de compartilhamento de arquivos:
  - semantica UNIX: toda escrita fica visivel imediatamente para todos (como se houvesse uma copia so);
  - semantica de SESSAO (AFS): cada cliente trabalha numa copia propria entre open e close; as mudancas so vao
    para o servidor no close, e o ultimo close sobrescreve tudo ("a ultima escrita vence").
Dois clientes acrescentam linhas ao mesmo arquivo de forma intercalada. Mostrar o resultado nas duas semanticas
e que na de sessao a atualizacao de um dos clientes e PERDIDA.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Passo { char cliente; string acao, texto; };

int main()
{
  vector<Passo> roteiro = {
    {'A', "open", ""}, {'B', "open", ""}, {'A', "append", "linha de A\n"},
    {'B', "append", "linha de B\n"}, {'A', "close", ""}, {'B', "close", ""}};

  // semantica UNIX: um unico arquivo compartilhado
  string unix = "inicio\n";
  for (auto &p : roteiro) if (p.acao == "append") unix += p.texto;

  // semantica de sessao: copias locais
  string servidor = "inicio\n", copiaA, copiaB;
  for (auto &p : roteiro) {
    string &copia = p.cliente == 'A' ? copiaA : copiaB;
    if (p.acao == "open") copia = servidor;             // baixa a versao atual
    else if (p.acao == "append") copia += p.texto;      // altera so a copia local
    else {                                              // close: envia a copia inteira
      servidor = copia;
      cout << "close de " << p.cliente << ": servidor agora tem\n" << servidor << "---" << endl;
    }
  }
  cout << "\nResultado com semantica UNIX:\n" << unix << "---" << endl;
  cout << "Resultado com semantica de sessao:\n" << servidor << "--- (a linha de A foi perdida)" << endl;
  return 0;
}
