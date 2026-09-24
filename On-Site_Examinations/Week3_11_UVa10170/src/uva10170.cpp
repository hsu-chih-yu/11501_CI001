#include <iostream>

using namespace std;

int main()
{
    long long s, d;
    while(cin >> s >> d){
        long long current_day = 0;
        while(current_day < d){
            current_day += s;
            s++;
        }
        cout << s - 1 << "\n";
    }
    return 0;
}