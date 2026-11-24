/*
Exercicio 3. Usando stack da STL, verificar se uma expressao tem parenteses, colchetes e chaves balanceados.
*/
#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool balanceada(const string &e)
{
  stack<char> p;
  for (char c : e) {
    if (c == '(' || c == '[' || c == '{') p.push(c);
    else if (c == ')' || c == ']' || c == '}') {
      if (p.empty()) return false;   // fechou sem abrir
      char a = p.top(); p.pop();
      if ((c == ')' && a != '(') || (c == ']' && a != '[') || (c == '}' && a != '{')) return false;
    }
  }
  return p.empty();   // sobrou algo aberto?
}

int main()
{
  string testes[] = {"{a*[b+(c-d)]}", "(a+b]", "((a)", "x+y)", "[()]{}"};
  for (const string &t : testes) cout << t << " -> " << (balanceada(t) ? "ok" : "erro") << endl;
  return 0;
}
