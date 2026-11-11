#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    
    int n;
    while(cin >> n && n != 0){
        int a[500001];
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n - i - 1; j++){
                if(a[j] > a[j+1]){
                    ans++;
                    int temp = a[j];
                    a[j] = a[j+1];
                    a[j + 1] = temp;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
