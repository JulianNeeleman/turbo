#ifndef GEOMETRY_SPHERE_H
#define GEOMETRY_SPHERE_H

#include <array>
#include <tuple>

#include "line_segment.hpp"
#include "point.hpp"

// N-dimensional sphere.
template <class T, unsigned N> struct Sphere {
    // Member variables.
    Point<T, N> c;
    T r;

    // Default constructor.
    Sphere() = default;

    // Assignment constructor.
    Sphere(const Point<T, N> &c, const T &r) : c(c), r(r) {}

    // Stream constructor.
    explicit Sphere(std::istream &stream) : c(stream) { stream >> r; }

    // Equality operator.
    bool operator==(const Sphere &rhs) const {
        return std::tie(c, r) == std::tie(rhs.c, rhs.r);
    }

    // Check if two spheres overlap.
    bool overlap(const Sphere &rhs) const {
        LineSegment<T, N> line(c, rhs.c);
        return line.sq_length() <= (r + rhs.r) * (r + rhs.r);
    }

    // Check if two spheres are tangent.
    bool tangent(const Sphere &rhs) const {
        LineSegment<T, N> line(c, rhs.c);
        return line.sq_length() == (r + rhs.r) * (r + rhs.r);
    }

    // Check if sphere contains other sphere.
    bool contains(const Sphere &rhs) const {
        LineSegment<T, N> line(c, rhs.c);
        return line.sq_length() <= (r - rhs.r) * (r - rhs.r);
    }

    // Check if two spheres intersect.
    bool intersects(const Sphere &rhs) const {
        return overlap(rhs) && !contains(rhs) && !rhs.contains(*this);
    }

    // Compute the intersections of two spheres.
    std::vector<Point<T, 2>> intersections(const Sphere<T, 2> &rhs) const {
        // The circles coincide or are disjunct.
        if (!intersects(rhs)) {
            return {};
        }

        // Compute midpoint.
        LineSegment<T, 2> ab(c, rhs.c);
        T l = ab.length();
        T a = (r * r - rhs.r * rhs.r + l * l) / (2 * l),
          h = std::sqrt(r * r - a * a);
        Point<T, 2> m = c + a * (rhs.c - c) / l;

        // Tangent point.
        if (tangent(rhs)) {
            return {m};
        }

        return {};
    }
};

#endif // GEOMETRY_SPHERE_H
