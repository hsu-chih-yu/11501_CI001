#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    double s, a;
    string b;
    const double PI = 2.0 * acos(0.0);

    while (cin >> s >> a >> b) {
        double r = s + 6440.0;
        
        if (b == "min") {
            a /= 60.0;
        }
        
        if (a > 180.0) {
            a = 360.0 - a;
        }
        
        double rad = a * PI / 180.0;
        double arc = r * rad;
        double chord = 2.0 * r * sin(rad / 2.0);
        
        cout << fixed << setprecision(6) << arc << " " << chord << "\n";
    }
    return 0;
}