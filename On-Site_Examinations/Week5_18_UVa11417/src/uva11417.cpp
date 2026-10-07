#include <iostream>
#include <cmath>

using namespace std;


long long getgcd(long long a, long long b){
    while(b != 0){
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return abs(a);
}


int main()
{
    int n;
    while(cin >> n && n != 0){
        int g = 0;
        for(int i = 1; i < n; i++){
            for(int j = i + 1 ; j <= n; j++){
                g += getgcd(i, j);
            }
        }
        cout << g << endl;
    }
    return 0;
}