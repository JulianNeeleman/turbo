#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../../lib/geometry/polygon.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::sqrt;
using std::vector;
using std::string;

int n;
vector<Point<int64_t, 2>> p;

bool attempt(int i, int j) {
    vector<bool> s(n);
    for (unsigned k = 0; k < n; k++) {
        if ((i == k) || (j == k)) {
            continue;
        }
        Polygon<int64_t> tgl({p[i], p[j], p[k]});
        if (tgl.orientation() != Orientation::CL) {
            s[k] = true;
        }
    }

    int oi = i, oj = j;
    i = -1, j = -1;
    for (unsigned k = 0; k < n && j == -1; k++) {
        if (s[k]) {
            i == -1 ? i = k : j = k;
        }
    }

    if (j == -1) {
        return i != -1;
    }

    for (unsigned k = 0; k < n; k++) {
        if ((i == k) || (j == k)) {
            continue;
        }
        Polygon<int64_t> tgl({p[i], p[j], p[k]});
        if ((s[k] && tgl.orientation() != Orientation::CL) ||
            (!s[k] && tgl.orientation() == Orientation::CL)) {
            return false;
        }
    }

    return (p[oj][1] - p[oi][1]) * (j - i) == (p[j][1] - p[i][1]) * (oj - oi);
}

int main() {
    cin >> n;
    p.assign(n, Point<int64_t, 2>({0, 0}));
    for (int i = 0; i < n; i++) {
        p[i][0] = i;
        cin >> p[i][1];
    }

    if (attempt(0, 1) || attempt(0, 2) || attempt(1, 2)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
