#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b;
    while(cin >> a >> b && a != -1 && b != -1){
         a = abs(b - a);
        int n = 100 - a;
        if(a < n){
            cout << a << endl;

        }else{
            cout << n << endl;
        }
    }
    return 0;
}