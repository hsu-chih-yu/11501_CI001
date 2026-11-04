#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin >> n && n != 0){
        int ans = 0;
        int b[100] = {};
        int t = 0;

        while(n > 0){
            if(n % 2 == 1){
                ans++;
                b[t] = 1;
            }
            t++;
            n /= 2;
        }
        cout << "The parity of ";
        for(int i = t - 1; i >= 0; i--){
            cout << b[i];
        }
        cout << " is " << ans << " (mod 2)." << endl;
    }
    return 0;
}
