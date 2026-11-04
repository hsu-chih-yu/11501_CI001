#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    int c = 1;
    while(cin >> n >> m && n != 0 && m != 0){
        vector<int> a;
        vector<int> b;
        
        for(int i = 0; i < n; i++){
            int t;
            cin >> t;
            a.push_back(t);
        }
        sort(a.begin(), a.end());
        cout << "CASE# " << c << ":" << endl;
        for(int i = 0; i < m; i++){
            bool f = false;
            int t;
            cin >> t;
            for(int j = 0; j < n; j++){
                if(a[j] == t){
                    cout << t << " found at " << j+1 << endl;
                    
                    f = true;
                    break;
                }
            }
            if(!f){
                cout << t << " not found\n";
            }
        }


        c++;
    }
    return 0;
}
