#include <iostream>

using namespace std;

int main()
{
    int k;
    while(cin >> k && k != 0){
        int a, b;
        cin >> a >> b;
        while(k--){
            int x, y;
            cin >> x >> y;
            if(x == a || y == b){
                cout << "divisa" << endl;
            }else if(x > a && y > b){
                cout << "NE" << endl;
            }else if(x > a && y < b){
                cout << "SE" << endl;
            }else if(x < a && y < b){
                cout << "SO" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}