#include <iostream>

using namespace std;

int binary(int n){
        int ans1 = 0;
        int t = 1024*16;
        int N = n;

        while(t != 1 ){
            if(n >= t){
                n -= t;
                ans1++;
            }
            t /= 2;
        }
        if(n == 1)ans1++;
        return ans1;
        }

int main()
{
    int c;
    cin >> c;
    while(c--){
        int n;
        cin >> n;
        int ans1 = 0;
        int t = 1024*16;
        int N = n;

        while(t != 1 ){
            if(n >= t){
                n -= t;
                ans1++;
            }
            t /= 2;
        }
        if(n == 1)ans1++;
        n = N;
        int ans2 = 0;
        while(n > 0){
            int k = n % 10;
            ans2 += binary(k);
            n /= 10;
        }
        cout << ans1 << " " << ans2 << endl;
    }
    return 0;
}
