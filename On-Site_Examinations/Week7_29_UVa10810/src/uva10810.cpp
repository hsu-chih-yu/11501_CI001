#include <iostream>
#include <vector>

using namespace std;

long long mergeCount(vector<long long>& a, vector<long long>& tmp, int l, int r){
    if(r - l <= 1) return 0;
    int mid = (l + r) / 2;
    long long cnt = mergeCount(a, tmp, l, mid) + mergeCount(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while(i < mid && j < r){
        if(a[i] <= a[j]){
            tmp[k++] = a[i++];
        }else{
            cnt += mid - i;
            tmp[k++] = a[j++];
        }
    }
    while(i < mid) tmp[k++] = a[i++];
    while(j < r) tmp[k++] = a[j++];
    for(int t = l; t < r; t++) a[t] = tmp[t];
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n && n != 0){
        vector<long long> a(n), tmp(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        cout << mergeCount(a, tmp, 0, n) << "\n";
    }
    return 0;
}
