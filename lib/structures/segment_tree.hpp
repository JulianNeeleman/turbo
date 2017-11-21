#ifndef STRUCTURES_SEGMENT_TREE_H
#define STRUCTURES_SEGMENT_TREE_H

#include <vector>

// Finite line segment.
template <class T> class SegmentTree {
  private:
    // Private member variables.
    unsigned n;
    std::vector<T> xs, tree;

    unsigned mid(unsigned l, unsigned r) const { return l + (r - l) / 2; }

    // Statically construct the tree from an array.
    T construct(unsigned l, unsigned r, unsigned i) {
        // Singleton.
        if (l == r) {
            tree[i] = xs[l];
            return xs[l];
        }

        unsigned m = mid(l, r);
        tree[i] = construct(l, m, i * 2 + 1) * construct(m + 1, r, i * 2 + 2);
        return tree[i];
    }

    // Compute the product of all elements in the intersection
    // of the given range and the query range.
    T query_impl(unsigned l, unsigned r, unsigned ql, unsigned qr,
                 unsigned i) const {
        // Contained in query range.
        if (ql <= l && qr >= r) {
            return tree[i];
        }

        // Outside of query range.
        if (r < ql || l > qr) {
            return T::identity();
        }

        unsigned m = mid(l, r);
        return query_impl(l, m, ql, qr, 2 * i + 1) *
               query_impl(m + 1, r, ql, qr, 2 * i + 2);
    }

    // Propagate an updated value in the array
    // through the tree.
    void update_impl(unsigned l, unsigned r, unsigned ui, const T &diff,
                     unsigned i) {
        // Outside of update range.
        if (ui < l || ui > r) {
            return;
        }

        tree[i] += diff;
        // Enter recursion if we haven't reached a singleton.
        if (l != r) {
            unsigned m = mid(l, r);
            update_impl(l, m, ui, diff, 2 * i + 1);
            update_impl(m + 1, r, ui, diff, 2 * i + 2);
        }
    }

  public:
    // Default constructor.
    SegmentTree() = default;

    // Assignment constructor.
    explicit SegmentTree(const std::vector<T> &xs)
        : n(xs.size()), xs(xs), tree(std::vector<T>(4 * n)) {
        construct(0, n - 1, 0);
    }

    T query(unsigned l, unsigned r) const {
        return query_impl(0, n - 1, l, r, 0);
    }

    void update(unsigned i, T value) {
        T diff = value - xs[i];
        update_impl(0, n - 1, i, diff, 0);
    }
};

#endif // STRUCTURES_SEGMENT_TREE_H
