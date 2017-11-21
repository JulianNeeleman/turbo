 #include <algorithm>
 #include <iomanip>
 #include <iostream>
 #include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::sqrt;
using std::vector;
using std::string;

int main() {
    int n;
    double h;
    cin >> n >> h;
    double c = 0.0;
    for (unsigned i = 0; i < n - 1; i++) {
        double x = sqrt(c * c + h * h / n);
        cout << setprecision(20) << x << " ";
        c = x;
    }

    cout << endl;
    return 0;
}
