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


    T operator[](unsigned i) const { return xs[i]; }


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
            p.xs[i] = xs[i] + rhs[i];
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
            m.xs[i] = (p[i] + q[i]) / 2;
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


    Point<T, 2> operator[](unsigned i) const { return ps[i]; }

  private:

    unsigned succ(unsigned i) const { return (i + 1) % ps.size(); }
};

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
        p[i].xs[0] = i;
        cin >> p[i].xs[1];
    }

    if (attempt(0, 1) || attempt(0, 2) || attempt(1, 2)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
