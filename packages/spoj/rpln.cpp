 #include <iostream>
 #include <vector>




 #include <vector>


template <class T> class SegmentTree {
  private:

    unsigned n;
    std::vector<T> xs, tree;

    unsigned mid(unsigned l, unsigned r) const { return l + (r - l) / 2; }


    T construct(unsigned l, unsigned r, unsigned i) {

        if (l == r) {
            tree[i] = xs[l];
            return xs[l];
        }

        unsigned m = mid(l, r);
        tree[i] = construct(l, m, i * 2 + 1) * construct(m + 1, r, i * 2 + 2);
        return tree[i];
    }



    T query_impl(unsigned l, unsigned r, unsigned ql, unsigned qr,
                 unsigned i) const {

        if (ql <= l && qr >= r) {
            return tree[i];
        }


        if (r < ql || l > qr) {
            return T::identity();
        }

        unsigned m = mid(l, r);
        return query_impl(l, m, ql, qr, 2 * i + 1) *
               query_impl(m + 1, r, ql, qr, 2 * i + 2);
    }



    void update_impl(unsigned l, unsigned r, unsigned ui, const T &diff,
                     unsigned i) {

        if (ui < l || ui > r) {
            return;
        }

        tree[i] += diff;

        if (l != r) {
            unsigned m = mid(l, r);
            update_impl(l, m, ui, diff, 2 * i + 1);
            update_impl(m + 1, r, ui, diff, 2 * i + 2);
        }
    }

  public:

    SegmentTree() = default;


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

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::vector;
using std::string;

struct Node {
    int64_t v;
    Node operator*(const Node &rhs) const { return Node{min(v, rhs.v)}; }

    static Node identity() { return {1 << 30}; }
};

int main() {
    unsigned T;
    cin >> T;
    for (unsigned t = 1; t <= T; t++) {
        cout << "Scenario #" << t << ":" << endl;
        unsigned N, Q;
        cin >> N >> Q;

        vector<Node> xs(N);
        for (unsigned i = 0; i < N; i++) {
            cin >> xs[i].v;
        }
        SegmentTree<Node> tree(xs);

        for (unsigned i = 0; i < Q; i++) {
            unsigned l, r;
            cin >> l >> r;
            cout << tree.query(l - 1, r - 1).v << endl;
        }
    }
    return 0;
}
