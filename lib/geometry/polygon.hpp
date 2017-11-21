#ifndef GEOMETRY_POLYGON_H
#define GEOMETRY_POLYGON_H

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>

template <class T> struct Polygon;

#include "line_segment.hpp"
#include "line_segment_set.hpp"
#include "orientation.hpp"
#include "point.hpp"

// N-dimensional polygon.
template <class T> struct Polygon {
    // Member variables.
    std::vector<Point<T, 2>> ps;

    // Default constructor.
    Polygon() = default;

    // Assignment constructor.
    explicit Polygon(const std::vector<Point<T, 2>> &ps) : ps(ps) {}

    // Stream constructor.
    explicit Polygon(std::istream &stream, unsigned length) {
        for (unsigned i = 0; i < length; i++) {
            ps.push_back(Point<T, 2>(stream));
        }
    }

    // Subscript access operator.
    const Point<T, 2> &operator[](unsigned i) const { return ps[i]; }
    Point<T, 2> &operator[](unsigned i) { return ps[i]; }

    // Serialize the polygon.
    std::string serialize() const {
        std::string s = std::to_string(ps.size()) + "\n";
        for (const Point<T, 2> p : ps) {
            s += p.serialize() + "\n";
        }
        return s;
    }

    // Calculate double the area of the polygon.
    T signed_double_area() const {
        T total = 0;
        for (unsigned i = 0; i < ps.size(); i++) {
            total += ps[i][0] * ps[succ(i)][1] - ps[succ(i)][0] * ps[i][1];
        }
        return total;
    }

    // Wrappers for retrieving the actual positive (double) area.
    T double_area() const { return std::abs(signed_double_area()); }
    T area() const { return double_area() / 2; }

    // Obtain all line segments.
    LineSegmentSet<T> line_segments() const {
        std::vector<LineSegment<T, 2>> segments;
        for (unsigned i = 0; i < ps.size(); i++) {
            segments.push_back(LineSegment<T, 2>(ps[i], ps[succ(i)]));
        }
        return LineSegmentSet<T>(segments);
    }

    // Determine whether the polygon is simple or self-intersecting.
    bool simple() const {
        return line_segments().intersecting().size() == ps.size();
    }

    // Convex hull algorithm.
    Polygon<T> convex_hull(const bool strict) const {
        // Sort points lexicographically.
        std::vector<Point<T, 2>> sorted(ps), hull(2 * ps.size());
        sort(sorted.begin(), sorted.end());
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

        int n = sorted.size(), k = 0;
        if (n == 1) {
            return Polygon<T>(sorted);
        }

        // Lower hull.
        for (int i = 0; i < n; i++) {
            Orientation o;
            do {
                o = Polygon<T>({hull[k - 2], hull[k - 1], sorted[i]})
                        .orientation();
            } while (k-- >= 2 && (o != CW || (!strict && o == CL)));
            hull[k++] = sorted[i];
        }

        // Upper hull.
        for (int i = n - 2, t = k + 1; i >= 0; i--) {
            Orientation o;
            do {
                o = Polygon<T>({hull[k - 2], hull[k - 1], sorted[i]})
                        .orientation();
            } while (k-- >= t && (o != CW || (!strict && o == CL)));
            hull[k++] = sorted[i];
        }

        hull.resize(k - 1);
        // Order the vertices clockwise.
        reverse(hull.begin(), hull.end());
        return Polygon<T>(hull);
    }

    // Determine the orientation of this polygon.
    Orientation orientation() const {
        T v = signed_double_area();
        return v == 0 ? Orientation::CL
                      : (v < 0 ? Orientation::CW : Orientation::CCW);
    }

    // Compute all angles.
    std::vector<T> angles() const {
        std::vector<T> as;
        std::vector<LineSegment<T, 2>> lines = line_segments();
        for (unsigned i = 0; i < lines.size(); i++) {
        }
    }

    // Compute all right angles.
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

    // Get a decremented circular point index.
    unsigned pred(unsigned i) const { return (i + ps.size() - 1) % ps.size(); }

    // Get an incremented circular point index.
    unsigned succ(unsigned i) const { return (i + 1) % ps.size(); }
};

#endif // GEOMETRY_POLYGON_H
