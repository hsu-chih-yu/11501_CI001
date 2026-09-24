#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        cin >> n;
        int a[10] = {};
        for(int i = 1; i <= n; i++){
                int temp = i;
            while(temp > 0){
                int t = temp % 10;
                a[t] ++;
                temp /= 10;
            }
        }
        for(int i = 0; i < 9; i++){
            cout << a[i] << " ";
        }
        cout << a[9] << endl;
    }
    return 0;
}