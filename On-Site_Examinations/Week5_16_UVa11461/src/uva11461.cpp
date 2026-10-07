#include <iostream>
#include <cmath>

using namespace std;

bool isSquare(long long n){
    if(n < 0)false;
    long long r = round(sqrt(n));
    return (r* r == n);

}


int main()
{
    int a,b;
    while(cin >> a >> b ){
            int ans = 0;
        if(a == 0 && b == 0)break;
        for(long long i = a; i <= b; i++){
            bool s = isSquare(i);
            if(s){
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}