#include <algorithm>
#include <iostream>
#include <vector>

#include "../../lib/geometry/line_segment.hpp"
#include "../../lib/geometry/sphere.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    int r, d;
    cin >> r >> d;

    Point<int, 2> origin({0, 0});
    Sphere<int, 2> a(origin, r - d), b(origin, r);

    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Sphere<int, 2> s(cin);
        LineSegment<int, 2> os(origin, s.c);
        if ((s.tangent(a) || !s.overlap(a)) && b.contains(s)) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
