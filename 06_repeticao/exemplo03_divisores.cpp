#include <iostream>
using namespace std;

bool divisivel(int x, int y){ return x % y == 0; }
int main(){
 int N;
 cout << "Digite um número: "; cin >> N;
 for (int i = 1; i <= N; i++)
   if (divisivel(N, i)) cout << i << endl;
 return 0;
}
