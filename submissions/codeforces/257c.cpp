#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../../lib/geometry/point.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::sqrt;
using std::vector;
using std::string;

int main() {
    int n;
    cin >> n;
    vector<Point<double, 2>> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = Point<double, 2>(cin);
    }

    Point<double, 2> orig({0, 0});
    sort(p.begin(), p.end(), sort_around_point<double>(orig));
    Polygon<double> s(p);
    for (int j = 0; j < n; j++) {
        cout << s[j].serialize() << endl;
        int i = s.pred(j), k = s.succ(j);
    }

    return 0;
}
