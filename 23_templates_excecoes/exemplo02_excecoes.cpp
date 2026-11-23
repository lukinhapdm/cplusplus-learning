/*
Exemplo 2. Excecoes: throw, try/catch, varios catch e excecao propria.
*/
#include <iostream>
#include <stdexcept>
using namespace std;

// excecao personalizada herda de std::exception
class SaldoInsuficiente : public exception {
public:
  const char *what() const noexcept override { return "Saldo insuficiente"; }
};

double divide(double a, double b)
{
  if (b == 0) throw invalid_argument("Divisao por zero");   // lanca o erro
  return a / b;
}

void saca(double &saldo, double v)
{
  if (v > saldo) throw SaldoInsuficiente();
  saldo -= v;
}

int main()
{
  try {
    cout << divide(10, 2) << endl;
    cout << divide(1, 0) << endl;   // pula direto para o catch
    cout << "nunca executa" << endl;
  } catch (const invalid_argument &e) {
    cout << "Erro: " << e.what() << endl;
  }

  double saldo = 100;
  try { saca(saldo, 500); }
  catch (const SaldoInsuficiente &e) { cout << "Erro: " << e.what() << endl; }
  catch (...) { cout << "Erro desconhecido" << endl; }   // pega qualquer outro
  return 0;
}
