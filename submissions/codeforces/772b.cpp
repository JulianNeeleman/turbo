#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../../lib/geometry/polygon.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::min;
using std::sqrt;
using std::vector;
using std::string;

int main() {
    int n;
    cin >> n;
    Polygon<double> p(cin, n);
    double ans = 1 << 30;
    for (int j = 0; j < n; j++) {
        int i = p.pred(j), k = p.succ(j);
        Polygon<double> tgl({p[i], p[j], p[k]});
        LineSegment<double, 2> base({p[i], p[k]});
        double h = 2 * tgl.area() / base.length();
        ans = min(ans, h / 2.0);
    }
    cout << setprecision(20) << ans << endl;
    return 0;
}
