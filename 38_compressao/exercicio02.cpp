/*
Exercicio 2. Compressao LZW (Lempel-Ziv-Welch), baseada em dicionario: substitui sequencias repetidas por
codigos de um dicionario que e construido durante a propria compressao (nao precisa ser transmitido).
Comprimir: comeca com os 256 caracteres; le o maior prefixo w ja presente no dicionario, emite o codigo de w
e insere w + proximo caractere como nova entrada.
Descomprimir: reconstroi o mesmo dicionario lendo os codigos. Caso especial: o codigo pode ser o que
acabou de ser criado (entrada = anterior + primeiro caractere do anterior).
*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

vector<int> comprime(const string &s)
{
  map<string, int> dic;
  for (int c = 0; c < 256; c++) dic[string(1, (char)c)] = c;
  vector<int> saida;
  string w;
  for (char c : s) {
    string wc = w + c;
    if (dic.count(wc)) w = wc;   // continua aumentando a sequencia
    else {
      saida.push_back(dic[w]);
      int novo = dic.size();
      dic[wc] = novo;            // nova entrada
      w = string(1, c);
    }
  }
  if (!w.empty()) saida.push_back(dic[w]);
  return saida;
}

string descomprime(const vector<int> &cod)
{
  vector<string> dic;
  for (int c = 0; c < 256; c++) dic.push_back(string(1, (char)c));
  string anterior = dic[cod[0]], s = anterior;
  for (size_t i = 1; i < cod.size(); i++) {
    string entrada;
    if (cod[i] < (int)dic.size()) entrada = dic[cod[i]];
    else entrada = anterior + anterior[0];   // caso especial: codigo ainda nao existe
    s += entrada;
    dic.push_back(anterior + entrada[0]);
    anterior = entrada;
  }
  return s;
}

int main()
{
  string texto = "TOBEORNOTTOBEORTOBEORNOT";
  vector<int> c = comprime(texto);
  cout << "Codigos: ";
  for (int x : c) cout << x << " ";
  cout << endl;
  // supondo 12 bits por codigo (dicionario de ate 4096 entradas) contra 8 bits por caractere
  cout << texto.size() << " caracteres (" << texto.size() * 8 << " bits) -> " << c.size() << " codigos ("
       << c.size() * 12 << " bits)" << endl;
  cout << "Descomprimido: " << descomprime(c) << (descomprime(c) == texto ? " (ok)" : " (ERRO)") << endl;

  string repetitivo(2000, 'a');
  cout << "2000 letras 'a' viram " << comprime(repetitivo).size() << " codigos" << endl;
  return 0;
}
