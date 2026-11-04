#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin >> n && n != 0){
        int ans = 0;
        int  b[100] = {};
        long long t = 0;


        while(n > 0){
            if(n % 2 == 1){
                ans++;
                b[t] = 1;
            }
            t++;
            n /= 2;
        }
        cout << "The parity of " ;
        int k = 0;
        for(int i = t - 1; i >= 0; i--){
            k = k * 10 + b[i];
        }
        cout << k ;
        cout << " is " << ans << " (mod 2)." << endl;
    }
    return 0;
}
