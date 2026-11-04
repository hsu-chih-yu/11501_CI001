#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin >> n && n >= 0){
        long long b = 0;
        long long t = 1;
        while(t <= n) t *= 3;
        while(t != 1){
            t /= 3;
            b *= 10;
            while(t <= n){
                n -= t;
                b++;
            }
        }
        printf("%lld\n", b);
    }
    return 0;
}
