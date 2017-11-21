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

int main() {
    Polygon<int> p(cin, 3);
    if (!p.right_angles().empty()) {
        cout << "RIGHT" << endl;
    } else {
        for (int i = 0; i < 3; i++) {
            for (int m : {1, -1}) {
                for (int d : {0, 1}) {
                    p[i][d] += m;
                    if (p.simple() && !p.right_angles().empty()) {
                        cout << "ALMOST" << endl;
                        return 0;
                    }
                    p[i][d] -= m;
                }
            }
        }
        cout << "NEITHER" << endl;
    }

    return 0;
}
