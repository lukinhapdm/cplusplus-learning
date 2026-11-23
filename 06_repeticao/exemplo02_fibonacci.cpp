#include <iostream>
using namespace std;

int main(){
 int N, a = 0, b = 1, c;
 cout << "Digite o numero de termos desejados: ";
 cin >> N;
 cout << b << endl;
 if (N == 1) return 0;
 for (int i = 2; i <= N; i++){ c = a + b; a = b; b = c; cout << c << endl; }
 return 0;
}
