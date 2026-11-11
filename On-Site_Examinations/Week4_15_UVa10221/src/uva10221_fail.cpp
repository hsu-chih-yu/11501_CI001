#include <iostream>
#include <string>

using namespace std;

int main()
{
    int s, a;
    string b;
    cout <<  3592.408346 / 6940 * 180 /3.1415926 << endl <<  124.616509 / 7140 * 360 / 3.1415926 *30 << endl;
    while(cin >> s >> a >> b){
        s += 6440;
        float o = 180 / 3.1415926;
        double ans = s * a * 3.1415926536 / 180;
        if(b == "min"){
            ans /= 60;
        }
        
        printf("%.6f %.6f\n", ans);
        }
    return 0;
}
