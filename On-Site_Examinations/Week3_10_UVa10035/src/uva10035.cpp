#include <iostream>

using namespace std;

int main()
{
    int a, b;
    while(cin >> a >> b && (a != 0 && b != 0)){
        int ans = 0;
        int count = 0;
        while(a > 0 || b > 0){
            int i = a % 10;
            int j = b % 10;
            if(i + j + count > 9){
                ans ++;
                count = 1;
            }else{
                count = 0;
            }
            a /= 10;
            b /= 10;
        }
        if(ans == 0){
            cout << "No carry operation.\n";
        }else if(ans == 1){
            printf("1 carry operation.\n");
        }else{
            printf("%d carry operations.\n", ans);
        }
    }
    return 0;
}