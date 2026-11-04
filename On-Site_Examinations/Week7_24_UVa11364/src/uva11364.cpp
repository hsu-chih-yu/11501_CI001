#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        cin >> n;
        int maxi = 0;
        int mini = 9999;
        int k;
        for(int i = 0; i < n; i++){
            cin >> k;
            maxi = max(maxi, k);
            mini = min(mini, k);
        }
        int ans = maxi - mini;
        ans *= 2;
        cout << ans << endl;
    }
    return 0;
}
