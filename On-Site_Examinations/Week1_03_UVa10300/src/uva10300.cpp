#include <iostream>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        while (n--) {
            int f;
            cin >> f;
            long long total_premium = 0;
            while (f--) {
                long long size, animals, friendliness;
                cin >> size >> animals >> friendliness;
                total_premium += size * friendliness;
            }
            cout << total_premium << "\n";
        }
    }
    return 0;
}