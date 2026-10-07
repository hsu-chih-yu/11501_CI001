#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int a, b;
        cin >> a >> b;
        if(b % a == 0){
            cout << a << " " << b << endl;
        }else{
            cout << "-1\n";
        }
    }
    return 0;
}