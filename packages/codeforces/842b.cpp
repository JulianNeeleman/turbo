 #include <algorithm>
 #include <iostream>
 #include <vector>




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


    std::string serialize() const {
        std::string s = "";
        for (const T &x : xs) {
            s += std::to_string(x) + " ";
        }
        s.pop_back();
        return s;
    }
};



 #include <algorithm>
 #include <cmath>
 #include <set>
 #include <vector>

template <class T> struct Polygon;





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


template <class T, unsigned N> struct LineSegment {

    Point<T, N> p, q;


    LineSegment(const Point<T, N> &p, const Point<T, N> &q) : p(p), q(q) {}


    bool intersect(const LineSegment &rhs) const {
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
};



 #include <array>




template <class T, unsigned N> struct Sphere {

    Point<T, N> c;
    T r;


    Sphere() = default;


    Sphere(const Point<T, N> &c, const T &r) : c(c), r(r) {}


    explicit Sphere(std::istream &stream) : c(stream) { stream >> r; }


    bool overlap(const Sphere &rhs) const {
        LineSegment<T, N> line(c, rhs.c);
        return line.sq_length() < (r + rhs.r) * (r + rhs.r);
    }


    bool tangent(const Sphere &rhs) const {
        LineSegment<T, N> line(c, rhs.c);
        return line.sq_length == (c.r + rhs.c.r) * (c.r + rhs.c.r);
    }


    bool contains(const Sphere &rhs) const {
        LineSegment<T, N> line(c, rhs.c);
        return line.sq_length() <= (r - rhs.r) * (r - rhs.r);
    }
};

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
        if (!s.overlap(a) && b.contains(s)) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
