#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(a == b && b == c && c == d){
            cout << "square" << endl;
            continue;
        }else if((a == b && c == d)||(a == c && b == d) || (a == d && b == c)){
            cout << "rectangle" << endl;
            continue;
        }
        int len[4]={a, b, c, d};
        for(int i = 0; i < 3; i++){
            if(len[i] > len[i+1]){
                int temp = len[i];
                len[i] = len[i+1];
                len[i+1] = temp;
            }
        }
        int sum = len[0]+len[1]+len[2];
        if(sum > len[3]){
            cout << "quadrangle" << endl;

        }else{
            cout << "banana" << endl;
        }
    }
    return 0;
}