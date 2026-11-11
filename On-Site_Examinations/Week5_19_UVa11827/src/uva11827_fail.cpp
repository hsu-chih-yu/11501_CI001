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

int main(){
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        char c = ' ';
        int i = 0;
        int a[101] = {};
        while(c != '\n'){
            cin >> n;
            a[i] = n;
            scanf("%c", &c);
            i++;
        }
        int m = 0;
        for(int j = 0; j < i - 1; j++){
            for(int k = j + 1; k < i; k++){
                int t = getgcd(a[j], a[k]);
                if(m < t){
                    m = t;
                }
            }
        }
        cout << m << endl;
    }
    return 0;
}
