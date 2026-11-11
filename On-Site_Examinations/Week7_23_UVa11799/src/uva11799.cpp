#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    for(int c = 1; c <= cases; c++){
        int n;
        cin >> n;
        int maxi = 0;
        for(int i = 0; i < n; i++){
            int speed;
            cin >> speed;
            maxi = max(maxi, speed);
        }
        printf("Case %d: %d\n", c, maxi);
    }
    return 0;
}
