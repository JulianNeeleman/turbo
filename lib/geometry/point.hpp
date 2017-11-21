#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include <array>

template <class T, unsigned N> struct Point;
template <class T> struct sort_around_point;

#include "polygon.hpp"

// N-dimensional point.
template <class T, unsigned N> struct Point {
    // Member variables.
    std::array<T, N> xs;

    // Default constructor.
    Point() = default;

    // Assignment constructor.
    explicit Point(const std::array<T, N> &xs) : xs(xs) {}

    // Stream constructor.
    explicit Point(std::istream &stream) {
        for (unsigned i = 0; i < N; i++) {
            stream >> xs[i];
        }
    };

    // Subscript access operators.
    const T &operator[](unsigned i) const { return xs[i]; }
    T &operator[](unsigned i) { return xs[i]; }

    // Equality operator.
    bool operator==(const Point<T, N> &rhs) const {
        for (unsigned i = 0; i < N; i++) {
            if (xs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }

    // Inequality operator.
    bool operator<(const Point<T, N> &rhs) const {
        for (unsigned i = 0; i < N; i++) {
            if (xs[i] != rhs[i]) {
                return xs[i] < rhs[i];
            }
        }
        return false;
    }

    // Addition operator.
    Point<T, N> operator+(const Point<T, N> &rhs) const {
        Point<T, N> p;
        for (unsigned i = 0; i < N; i++) {
            p[i] = xs[i] + rhs[i];
        }
        return p;
    }

    // Subtraction operator.
    Point<T, N> operator-(const Point<T, N> &rhs) const {
        Point<T, N> p;
        for (unsigned i = 0; i < N; i++) {
            p.xs[i] = xs[i] - rhs[i];
        }
        return p;
    }

    // Serialize the point.
    std::string serialize() const {
        std::string s = "";
        for (const T &x : xs) {
            s += std::to_string(x) + " ";
        }
        s.pop_back();
        return s;
    }
};

// Sort functor for ordering points around a central point.
template <class T> struct sort_around_point {
    Point<T, 2> orig;

    explicit sort_around_point(const Point<T, 2> &orig) : orig(orig) {}

    inline bool operator()(const Point<T, 2> &lhs, const Point<T, 2> &rhs) {
        Point<T, 2> dl = lhs - orig, dr = rhs - orig;
        return atan2(dl[1], dl[0]) < atan2(dr[1], dr[0]);
    }
};

#endif // GEOMETRY_POINT_H
