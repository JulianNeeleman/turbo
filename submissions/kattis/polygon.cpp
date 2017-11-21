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
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            return 0;
        }
        Polygon<int> p(cin, n);
        cout << (p.simple() ? "YES" : "NO") << endl;
    }
    return 0;
}
