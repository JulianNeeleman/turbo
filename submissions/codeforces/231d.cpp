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
    Point<int, 3> p(cin), q(cin);
    vector<int> a(6);
    for (int i : {1, 2, 0}) {
        cin >> a[2 * i] >> a[2 * i + 1];
    }

    int ans = 0;
    for (int i = 0; i < 3; i++) {
        if (p[i] < 0) {
            ans += a[2 * i];
        } else if (p[i] > q[i]) {
            ans += a[2 * i + 1];
        }
    }

    cout << ans << endl;
    return 0;
}
