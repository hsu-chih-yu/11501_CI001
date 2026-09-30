#include <iostream>

using namespace std;

int main() {
    int nh, nt, ah, att;
    while (cin >> nh >> nt >> ah >> att) {
        if (nh == 0 && nt == 0 && ah == 0 && att == 0) break;
        int now = nh * 60 + nt;
        int al = ah * 60 + att;
        int d = al - now;
        if (d < 0) {
            d += 1440;
        }
        cout << d << endl;
    }
    return 0;
}