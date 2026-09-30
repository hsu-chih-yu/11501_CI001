#include <iostream>

using namespace std;

int main()
{
    int a, b;
    while(scanf("%d:%d", &a, &b)){
        if(a == 0 && b == 0)break;
        float da = 30 * a + 0.5 * b;
        if(da == 360){
            da = 0;
        }
        float db = 6 * b;
        float ans = da - db;
        if(ans < 0){
            ans += 360;
        }
        if(ans >= 180){
            ans = 360 - ans;
        }

        printf("%.3f\n", ans);
    }
    return 0;
}