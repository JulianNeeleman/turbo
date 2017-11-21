#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../../lib/geometry/polygon.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::sqrt;
using std::vector;
using std::string;

int main() {
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int n;
        cin >> n;
        Polygon<int> p(cin, n), hull = p.convex_hull(false);
    }
    return 0;
}
