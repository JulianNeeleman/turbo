#include <algorithm>
#include <iostream>
#include <vector>

#include "../../lib/geometry/line_segment.hpp"
#include "../../lib/geometry/polygon.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    std::vector<Point<int64_t, 2>> p(3);
    for (int i = 0; i < 3; i++) {
        p[i] = Point<int64_t, 2>(cin);
    }

    Polygon<int64_t> poly(p);
    if (poly.orientation() == Orientation::CL) {
        cout << "NO" << endl;
        return 0;
    }

    LineSegment<int64_t, 2> ab(p[0], p[1]), bc(p[1], p[2]);
    cout << (ab.sq_length() == bc.sq_length() ? "YES" : "NO") << endl;

    return 0;
}
