 #include <iomanip>
 #include <iostream>




 #include <algorithm>
 #include <cmath>
 #include <set>
 #include <vector>

template <class T> struct Polygon;




template <class T, unsigned N> struct LineSegment;




 #include <array>


template <class T, unsigned N> struct Vector {

    std::array<T, N> xs;


    Vector() = default;


    explicit Vector(const std::array<T, N> &xs) : xs(xs) {}


    explicit Vector(std::istream &stream) {
        for (unsigned i = 0; i < N; i++) {
            stream >> xs[i];
        }
    };


    std::string serialize() const {
        std::string s = "";
        for (const T &x : xs) {
            s += std::to_string(x) + " ";
        }
        s.pop_back();
        return s;
    }


    T operator[](unsigned i) const { return xs[i]; }


    bool operator==(const Vector<T, N> &rhs) const {
        for (unsigned i = 0; i < N; i++) {
            if (xs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }


    bool operator<(const Vector<T, N> &rhs) const {
        for (unsigned i = 0; i < N; i++) {
            if (xs[i] != rhs[i]) {
                return xs[i] < rhs[i];
            }
        }
        return false;
    }
};


template <class T, unsigned N> struct LineSegment {

    Vector<T, N> p, q;


    LineSegment(const Vector<T, N> &p, const Vector<T, N> &q) : p(p), q(q) {}


    bool intersect(const LineSegment &rhs) const {
        return Polygon<T>({p, q, rhs.p}).orientation() !=
                   Polygon<T>({p, q, rhs.q}).orientation() &&
               Polygon<T>({rhs.p, rhs.q, p}).orientation() !=
                   Polygon<T>({rhs.p, rhs.q, q}).orientation();
    }


    T length() const {
        T s = 0;
        for (unsigned i = 0; i < N; i++) {
            s += (p[i] - q[i]) * (p[i] - q[i]);
        }
        return std::sqrt(s);
    }
};




enum Orientation { CW, CCW, CL };



template <class T> struct Polygon {

    std::vector<Vector<T, 2>> ps;


    Polygon() = default;


    explicit Polygon(const std::vector<Vector<T, 2>> &ps) : ps(ps) {}


    explicit Polygon(std::istream &stream, unsigned length) {
        for (unsigned i = 0; i < length; i++) {
            ps.push_back(Vector<T, 2>(stream));
        }
    }


    std::string serialize() const {
        std::string s = std::to_string(ps.size()) + "\n";
        for (const Vector<T, 2> p : ps) {
            s += p.serialize() + "\n";
        }
        return s;
    }


    T signed_double_area() const {
        T total = 0;
        for (unsigned i = 0; i < ps.size(); i++) {
            total += ps[i][0] * ps[succ(i)][1] - ps[succ(i)][0] * ps[i][1];
        }
        return total;
    }


    T double_area() const { return std::abs(signed_double_area()); }


    bool simple() const {
        for (unsigned i = 0; i < ps.size(); i++) {
            LineSegment<T, 2> lhs(ps[i], ps[succ(i)]);
            for (unsigned j = succ(i) == 0; j + 1 < i; j++) {
                LineSegment<T, 2> rhs(ps[j], ps[succ(j)]);
                if (lhs.intersect(rhs)) {
                    return false;
                }
            }
        }
        return true;
    }


    Polygon<T> convex_hull() const {

        std::vector<Vector<T, 2>> sorted(ps), hull(2 * ps.size());
        sort(sorted.begin(), sorted.end());
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

        int n = sorted.size(), k = 0;
        if (n == 1) {
            return Polygon<T>(sorted);
        }


        for (int i = 0; i < n; i++) {
            while (k >= 2 &&
                   Polygon<T>({hull[k - 2], hull[k - 1], sorted[i]})
                           .orientation() != Orientation::CW) {
                k--;
            }
            hull[k++] = sorted[i];
        }


        for (int i = n - 2, t = k + 1; i >= 0; i--) {
            while (k >= t &&
                   Polygon<T>({hull[k - 2], hull[k - 1], sorted[i]})
                           .orientation() != Orientation::CW) {
                k--;
            }
            hull[k++] = sorted[i];
        }

        hull.resize(k - 1);

        reverse(hull.begin(), hull.end());
        return Polygon<T>(hull);
    }


    Orientation orientation() const {
        T v = signed_double_area();
        return v == 0 ? Orientation::CL
                      : (v < 0 ? Orientation::CW : Orientation::CCW);
    }


    Vector<T, 2> operator[](unsigned i) const { return ps[i]; }

  private:

    unsigned succ(unsigned i) const { return (i + 1) % ps.size(); }
};

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::min;

int main() {
    Vector<double, 2> u(cin);

    int n;
    cin >> n;

    double ans = 1 << 16;
    for (int i = 0; i < n; i++) {
        Vector<double, 2> v(cin);
        double s;
        cin >> s;

        ans = min(ans, LineSegment<double, 2>(u, v).length() / s);
    }

    cout << std::setprecision(20) << ans << endl;
    return 0;
}
