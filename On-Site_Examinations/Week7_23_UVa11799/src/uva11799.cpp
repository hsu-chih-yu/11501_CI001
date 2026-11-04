#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

int main()
{
    int cases;
    cin >> cases;
    int i = 1;
    while(cases--){

        char c = ' ';
        int maxi = -1;
        while(c == ' '){
            int n;
            cin >> n;
            if(n > maxi){
                maxi = n;
            }
            c = getchar();
        }
        printf("Case %d: %d\n", i, maxi);
        i++;
    }
    return 0;
}
