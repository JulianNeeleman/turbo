#ifndef GEOMETRY_LINE_SEGMENT_SET_H
#define GEOMETRY_LINE_SEGMENT_SET_H

#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <vector>

template <class T> struct LineSegmentSet;

#include "line_segment.hpp"
#include "orientation.hpp"
#include "point.hpp"

// Set of line segments.
template <class T> struct LineSegmentSet {
    // Local structs.
    struct Event {};

    // Member variables.
    std::vector<LineSegment<T, 2>> ps;
    std::vector<Event> es;

    // Default constructor.
    LineSegmentSet() = default;

    // Assignment constructor.
    explicit LineSegmentSet(const std::vector<LineSegment<T, 2>> &ps)
        : ps(ps) {}

    // Subscript access operator.
    const Point<T, 2> &operator[](unsigned i) const { return ps[i]; }
    Point<T, 2> &operator[](unsigned i) { return ps[i]; }

    // Find all intersecting pairs of lines.
    std::vector<std::pair<unsigned, unsigned>> intersecting() const {
        std::priority_queue<Point<T, 2>> pq;
        return {};
    }
};

#endif // GEOMETRY_LINE_SEGMENT_SET_H
