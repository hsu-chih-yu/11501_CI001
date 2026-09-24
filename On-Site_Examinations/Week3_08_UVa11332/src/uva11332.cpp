#include <iostream>

using namespace std;

int main()
{
    int n;
    while(cin >> n && n != 0){
        while(n >= 10){
            int t = n;
            int ans = 0;
            while(t > 0){
                ans += t % 10;
                t /= 10;
            }
            n = ans;
        }
        cout << n << endl;
    }
    return 0;
}