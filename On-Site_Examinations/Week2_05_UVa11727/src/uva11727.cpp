#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    for(int n = 1; n <= cases; n++){
        int a[3];
        cin >> a[0] >> a[1] >> a[2];
        for(int j = 0; j < 3; j++){
            for(int i = 0; i < 2; i++){
                if(a[i] > a[i+1]){
                    int temp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = temp;
                }
            }
        }
        printf("Case %d: %d\n", n, a[1]);
    }
    return 0;
}