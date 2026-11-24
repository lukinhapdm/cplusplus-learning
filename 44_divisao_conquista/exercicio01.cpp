/*
Exercicio 1. Multiplicacao de inteiros grandes (strings de digitos) pelo algoritmo de Karatsuba.
Escrevendo x = a*10^m + b e y = c*10^m + d:  x*y = ac*10^(2m) + (ad + bc)*10^m + bd.
Em vez de 4 multiplicacoes de metade do tamanho, usa 3: ac, bd e (a+b)(c+d), pois ad + bc = (a+b)(c+d) - ac - bd.
T(n) = 3T(n/2) + O(n) = O(n^log2(3)) = O(n^1.585), contra O(n^2) do metodo da escola.
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long long multDigitos;   // multiplicacoes de um digito por outro

string tiraZeros(string s) { size_t i = s.find_first_not_of('0'); return i == string::npos ? "0" : s.substr(i); }

string soma(string a, string b)
{
  string r;
  int i = a.size() - 1, j = b.size() - 1, vai = 0;
  while (i >= 0 || j >= 0 || vai) {
    int s = vai + (i >= 0 ? a[i--] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
    r += char('0' + s % 10); vai = s / 10;
  }
  reverse(r.begin(), r.end());
  return tiraZeros(r);
}

string subtrai(string a, string b)   // supoe a >= b
{
  string r;
  int i = a.size() - 1, j = b.size() - 1, emp = 0;
  while (i >= 0) {
    int s = (a[i--] - '0') - emp - (j >= 0 ? b[j--] - '0' : 0);
    emp = s < 0; if (s < 0) s += 10;
    r += char('0' + s);
  }
  reverse(r.begin(), r.end());
  return tiraZeros(r);
}

string escola(const string &a, const string &b)   // metodo tradicional O(n^2)
{
  string r(a.size() + b.size(), '0');
  for (int i = a.size() - 1; i >= 0; i--) {
    int vai = 0;
    for (int j = b.size() - 1; j >= 0; j--) {
      multDigitos++;
      int s = (r[i + j + 1] - '0') + (a[i] - '0') * (b[j] - '0') + vai;
      r[i + j + 1] = '0' + s % 10; vai = s / 10;
    }
    r[i] += vai;
  }
  return tiraZeros(r);
}

string karatsuba(string x, string y)
{
  int n = max(x.size(), y.size());
  if (n <= 1) { multDigitos++; return to_string((x[0] - '0') * (y[0] - '0')); }
  x = string(n - x.size(), '0') + x;   // mesmo tamanho
  y = string(n - y.size(), '0') + y;
  int m = n / 2;                       // digitos da parte baixa
  string a = x.substr(0, n - m), b = x.substr(n - m), c = y.substr(0, n - m), d = y.substr(n - m);
  string ac = karatsuba(a, c), bd = karatsuba(b, d);
  string meio = subtrai(subtrai(karatsuba(soma(a, b), soma(c, d)), ac), bd);   // ad + bc
  return soma(soma(ac + string(2 * m, '0'), meio + string(m, '0')), bd);
}

int main()
{
  cout << "1234 x 5678 = " << karatsuba("1234", "5678") << " (5678 * 1234 = " << 5678 * 1234 << ")" << endl;
  string x, y;
  for (int i = 0; i < 256; i++) { x += char('0' + (i * 7 + 3) % 10); y += char('0' + (i * 3 + 1) % 10); }
  multDigitos = 0; string e = escola(x, y); long long me = multDigitos;
  multDigitos = 0; string k = karatsuba(x, y); long long mk = multDigitos;
  cout << "256 x 256 digitos: resultados " << (e == k ? "iguais" : "DIFERENTES") << endl;
  cout << "  escola: " << me << " multiplicacoes de digitos, Karatsuba: " << mk << endl;
  return 0;
}
