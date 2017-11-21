#ifndef GEOMETRY_LINE_SEGMENT_H
#define GEOMETRY_LINE_SEGMENT_H

template <class T, unsigned N> struct LineSegment;

#include "orientation.hpp"
#include "point.hpp"
#include "polygon.hpp"

// Finite line segment.
template <class T, unsigned N> struct LineSegment {
    // Member variables.
    Point<T, N> p, q;

    // Assignment constructor.
    LineSegment(const Point<T, N> &p, const Point<T, N> &q) : p(p), q(q) {}

    // Check if two line segments overlap.
    bool overlap(const LineSegment<T, 2> &rhs) const {
        return Polygon<T>({p, q, rhs.p}).orientation() == Orientation::CL &&
               (overlap_util(rhs.p) || overlap_util(rhs.q));
    }

    // Determine whether this line segment intersects another.
    bool intersect(const LineSegment<T, 2> &rhs) const {
        Orientation a = Polygon<T>({p, q, rhs.p}).orientation(),
                    b = Polygon<T>({p, q, rhs.q}).orientation(),
                    c = Polygon<T>({rhs.p, rhs.q, p}).orientation(),
                    d = Polygon<T>({rhs.p, rhs.q, q}).orientation();
        return (a != b && c != d) || overlap(rhs) || rhs.overlap(*this);
    }

    // Squared Euclidean length of the line segment.
    T sq_length() const {
        T s = 0;
        for (unsigned i = 0; i < N; i++) {
            s += (p[i] - q[i]) * (p[i] - q[i]);
        }
        return s;
    }

    // Euclidean length of the line segment.
    T length() const { return std::sqrt(sq_length()); }

    // Mirror a point across the line segment.
    Point<T, N> midpoint() const {
        Point<T, N> m;
        for (unsigned i = 0; i < N; i++) {
            m[i] = (p[i] + q[i]) / 2;
        }
        return m;
    }

    // Double the line segment.
    LineSegment<T, N> double_segment() const {
        return LineSegment<T, N>(p, q + (q - p));
    }

  private:
    // Check if line contains a point.
    bool overlap_util(const Point<T, N> &r) const {
        for (unsigned i = 0; i < N; i++) {
            if (r[i] < std::min(p[i], q[i]) || r[i] > std::max(p[i], q[i])) {
                return false;
            }
        }
        return true;
    }
};

#endif // GEOMETRY_LINE_SEGMENT_H
