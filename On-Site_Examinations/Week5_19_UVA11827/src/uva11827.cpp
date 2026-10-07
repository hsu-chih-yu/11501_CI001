#include <iostream>
#include <string>
#include <sstream>
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
    if (cin >> cases) {
        string line;
        getline(cin, line);

        while(cases--){
            getline(cin, line);
            stringstream ss(line);

            int a[101] = {};
            int i = 0;
            int n;

            while(ss >> n){
                a[i++] = n;
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
            cout << m << "\n";
        }
    }
    return 0;
}