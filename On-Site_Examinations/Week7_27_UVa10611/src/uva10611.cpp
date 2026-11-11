#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int m;
    cin >> m;
    vector<int> mt(m);
    for(int i = 0; i < m; i++){
        cin >> mt[i];
    }
    sort(mt.begin(), mt.end());

    int n;
    cin >> n;
    while(n--){
        int h;
        cin >> h;

        // 第一個 >= h 的位置，它的前一個就是嚴格比 h 矮的最高者
        auto lo = lower_bound(mt.begin(), mt.end(), h);
        // 第一個 > h 的位置，就是嚴格比 h 高的最矮者
        auto hi = upper_bound(mt.begin(), mt.end(), h);

        if(lo == mt.begin()){
            cout << "X ";
        }else{
            cout << *(lo - 1) << " ";
        }

        if(hi == mt.end()){
            cout << "X\n";
        }else{
            cout << *hi << "\n";
        }
    }
    return 0;
}
