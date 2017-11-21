#include <iomanip>
#include <iostream>

#include "../../lib/geometry/polygon.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::min;

int main() {
    Point<double, 2> u(cin);

    int n;
    cin >> n;

    double ans = 1 << 16;
    for (int i = 0; i < n; i++) {
        Point<double, 2> v(cin);
        double s;
        cin >> s;

        ans = min(ans, LineSegment<double, 2>(u, v).length() / s);
    }

    cout << std::setprecision(20) << ans << endl;
    return 0;
}
