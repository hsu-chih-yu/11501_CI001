#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int m;
    cin >> m;
    vector<int> mt;
    for(int i = 0; i < m ;i++){
        int t;
        cin >> t;
        mt.push_back(t);
    }
    sort(mt.begin(), mt.end());
    
    int n;
    cin >> n;
    while(n--){
        int h;
        int ans = -1;
        cin >> h;
        int i;
        int ans2 = -1;
        for(i = 0; i < m; i++){
            if(mt[i] < h){
                ans = mt[i];
            }
            if(mt[i] > h){
                ans2 = mt[i];
                break;
            }
        }
        
        
        if(ans == -1){
            cout << "X ";
        }else{
            cout << ans << " ";
        }

        if(ans2 == -1){
            cout << "X\n";
        }else{
            cout << ans2 << endl;
        }
    }
    return 0;
}
