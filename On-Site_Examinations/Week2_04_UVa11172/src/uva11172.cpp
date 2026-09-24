#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int a, b;
        cin >> a >> b;
        if(a > b){
            cout << ">";
        }else if(a == b){
            cout << "=";
        }else if(a < b){
            cout << "<";
        }
        cout << endl;
    }
    return 0;
}