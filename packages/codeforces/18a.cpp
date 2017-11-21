 #include <algorithm>
 #include <iomanip>
 #include <iostream>
 #include <vector>




 #include <algorithm>
 #include <cmath>
 #include <set>
 #include <vector>

template <class T> struct Polygon;




template <class T, unsigned N> struct LineSegment;




 #include <array>


template <class T, unsigned N> struct Point {

    std::array<T, N> xs;


    Point() = default;


    explicit Point(const std::array<T, N> &xs) : xs(xs) {}


    explicit Point(std::istream &stream) {
        for (unsigned i = 0; i < N; i++) {
            stream >> xs[i];
        }
    };


    const T &operator[](unsigned i) const { return xs[i]; }
    T &operator[](unsigned i) { return xs[i]; }


    bool operator==(const Point<T, N> &rhs) const {
        for (unsigned i = 0; i < N; i++) {
            if (xs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }


    bool operator<(const Point<T, N> &rhs) const {
        for (unsigned i = 0; i < N; i++) {
            if (xs[i] != rhs[i]) {
                return xs[i] < rhs[i];
            }
        }
        return false;
    }


    Point<T, N> operator+(const Point<T, N> &rhs) const {
        Point<T, N> p;
        for (unsigned i = 0; i < N; i++) {
            p[i] = xs[i] + rhs[i];
        }
        return p;
    }


    Point<T, N> operator-(const Point<T, N> &rhs) const {
        Point<T, N> p;
        for (unsigned i = 0; i < N; i++) {
            p.xs[i] = xs[i] - rhs[i];
        }
        return p;
    }


    std::string serialize() const {
        std::string s = "";
        for (const T &x : xs) {
            s += std::to_string(x) + " ";
        }
        s.pop_back();
        return s;
    }
};


template <class T, unsigned N> struct LineSegment {

    Point<T, N> p, q;


    LineSegment(const Point<T, N> &p, const Point<T, N> &q) : p(p), q(q) {}


    bool intersect(const LineSegment<T, 2> &rhs) const {
        return Polygon<T>({p, q, rhs.p}).orientation() !=
                   Polygon<T>({p, q, rhs.q}).orientation() &&
               Polygon<T>({rhs.p, rhs.q, p}).orientation() !=
                   Polygon<T>({rhs.p, rhs.q, q}).orientation();
    }


    T sq_length() const {
        T s = 0;
        for (unsigned i = 0; i < N; i++) {
            s += (p[i] - q[i]) * (p[i] - q[i]);
        }
        return s;
    }


    T length() const { return std::sqrt(sq_length()); }


    Point<T, N> midpoint() const {
        Point<T, N> m;
        for (unsigned i = 0; i < N; i++) {
            m[i] = (p[i] + q[i]) / 2;
        }
        return m;
    }


    LineSegment<T, N> double_segment() const {
        return LineSegment<T, N>(p, q + (q - p));
    }
};




enum Orientation { CW, CCW, CL };



template <class T> struct Polygon {

    std::vector<Point<T, 2>> ps;


    Polygon() = default;


    explicit Polygon(const std::vector<Point<T, 2>> &ps) : ps(ps) {}


    explicit Polygon(std::istream &stream, unsigned length) {
        for (unsigned i = 0; i < length; i++) {
            ps.push_back(Point<T, 2>(stream));
        }
    }


    const Point<T, 2> &operator[](unsigned i) const { return ps[i]; }
    Point<T, 2> &operator[](unsigned i) { return ps[i]; }


    std::string serialize() const {
        std::string s = std::to_string(ps.size()) + "\n";
        for (const Point<T, 2> p : ps) {
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
    T area() const { return double_area() / 2; }


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

        std::vector<Point<T, 2>> sorted(ps), hull(2 * ps.size());
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


    std::vector<Point<T, 2>> right_angles() const {
        std::vector<Point<T, 2>> right;
        for (unsigned i = 0; i < ps.size(); i++) {
            LineSegment<T, 2> a(ps[pred(i)], ps[i]), b(ps[i], ps[succ(i)]),
                c(ps[pred(i)], ps[succ(i)]);
            if (a.sq_length() + b.sq_length() == c.sq_length()) {
                right.push_back(ps[i]);
            }
        }
        return right;
    }

  private:

    unsigned pred(unsigned i) const { return (i + ps.size() - 1) % ps.size(); }


    unsigned succ(unsigned i) const { return (i + 1) % ps.size(); }
};

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
