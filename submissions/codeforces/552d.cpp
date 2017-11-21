#include <algorithm>
#include <iostream>
#include <vector>

#include "../../lib/geometry/point.hpp"
#include "../../lib/geometry/polygon.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    int n;
    cin >> n;

    vector<Point<int, 2>> p = Polygon<int>(cin, n).ps;
    for (int i = 0; i < n - 2; i++) {
        sort(p.begin() + i + 1, p.end(), sort_around_point<int>(p[i]));
        cout << p[i].serialize() << endl;
        for (int j = i + 1; j < n - 1; j++) {
            int lo = j + 1, hi = n - 1;
            while (lo + 1 < hi) {
                int m = (lo + hi) / 2;
            }
        }
    }

    return 0;
}
