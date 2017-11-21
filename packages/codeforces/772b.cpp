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





enum Orientation { CW, CCW, CL };



 #include <array>

template <class T, unsigned N> struct Point;
template <class T> struct sort_around_point;



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


template <class T> struct sort_around_point {
    Point<T, 2> orig;

    explicit sort_around_point(const Point<T, 2> &orig) : orig(orig) {}

    inline bool operator()(const Point<T, 2> &lhs, const Point<T, 2> &rhs) {
        Point<T, 2> dl = lhs - orig, dr = rhs - orig;
        return atan2(dl[1], dl[0]) < atan2(dr[1], dr[0]);
    }
};



template <class T, unsigned N> struct LineSegment {

    Point<T, N> p, q;


    LineSegment(const Point<T, N> &p, const Point<T, N> &q) : p(p), q(q) {}


    bool overlap(const LineSegment<T, 2> &rhs) const {
        return Polygon<T>({p, q, rhs.p}).orientation() == Orientation::CL &&
               (overlap_util(rhs.p) || overlap_util(rhs.q));
    }


    bool intersect(const LineSegment<T, 2> &rhs) const {
        Orientation a = Polygon<T>({p, q, rhs.p}).orientation(),
                    b = Polygon<T>({p, q, rhs.q}).orientation(),
                    c = Polygon<T>({rhs.p, rhs.q, p}).orientation(),
                    d = Polygon<T>({rhs.p, rhs.q, q}).orientation();
        return (a != b && c != d) || overlap(rhs) || rhs.overlap(*this);
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

  private:

    bool overlap_util(const Point<T, N> &r) const {
        for (unsigned i = 0; i < N; i++) {
            if (r[i] < std::min(p[i], q[i]) || r[i] > std::max(p[i], q[i])) {
                return false;
            }
        }
        return true;
    }
};



 #include <algorithm>
 #include <cmath>
 #include <queue>
 #include <set>
 #include <vector>

template <class T> struct LineSegmentSet;






template <class T> struct LineSegmentSet {

    struct Event {};


    std::vector<LineSegment<T, 2>> ps;
    std::vector<Event> es;


    LineSegmentSet() = default;


    explicit LineSegmentSet(const std::vector<LineSegment<T, 2>> &ps)
        : ps(ps) {}


    const Point<T, 2> &operator[](unsigned i) const { return ps[i]; }
    Point<T, 2> &operator[](unsigned i) { return ps[i]; }


    std::vector<std::pair<unsigned, unsigned>> intersecting() const {
        std::priority_queue<Point<T, 2>> pq;
        return {};
    }
};




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


    LineSegmentSet<T> line_segments() const {
        std::vector<LineSegment<T, 2>> segments;
        for (unsigned i = 0; i < ps.size(); i++) {
            segments.push_back(LineSegment<T, 2>(ps[i], ps[succ(i)]));
        }
        return LineSegmentSet<T>(segments);
    }


    bool simple() const {
        return line_segments().intersecting().size() == ps.size();
    }


    Polygon<T> convex_hull(const bool strict) const {

        std::vector<Point<T, 2>> sorted(ps), hull(2 * ps.size());
        sort(sorted.begin(), sorted.end());
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

        int n = sorted.size(), k = 0;
        if (n == 1) {
            return Polygon<T>(sorted);
        }


        for (int i = 0; i < n; i++) {
            Orientation o;
            do {
                o = Polygon<T>({hull[k - 2], hull[k - 1], sorted[i]})
                        .orientation();
            } while (k-- >= 2 && (o != CW || (!strict && o == CL)));
            hull[k++] = sorted[i];
        }


        for (int i = n - 2, t = k + 1; i >= 0; i--) {
            Orientation o;
            do {
                o = Polygon<T>({hull[k - 2], hull[k - 1], sorted[i]})
                        .orientation();
            } while (k-- >= t && (o != CW || (!strict && o == CL)));
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


    unsigned pred(unsigned i) const { return (i + ps.size() - 1) % ps.size(); }


    unsigned succ(unsigned i) const { return (i + 1) % ps.size(); }
};

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::min;
using std::sqrt;
using std::vector;
using std::string;

int main() {
    int n;
    cin >> n;
    Polygon<double> p(cin, n);
    double ans = 1 << 30;
    for (int j = 0; j < n; j++) {
        int i = p.pred(j), k = p.succ(j);
        Polygon<double> tgl({p[i], p[j], p[k]});
        LineSegment<double, 2> base({p[i], p[k]});
        double h = 2 * tgl.area() / base.length();
        ans = min(ans, h / 2.0);
    }
    cout << setprecision(20) << ans << endl;
    return 0;
}
