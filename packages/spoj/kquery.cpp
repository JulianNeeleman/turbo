 #include <algorithm>
 #include <iostream>
 #include <set>
 #include <tuple>
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
using std::vector;
using std::set;
using std::pair;
using std::tie;

struct Node {
    int s;

    Node operator*(const Node &rhs) const { return Node{s + rhs.s}; }
    Node operator-(const Node &rhs) const { return Node{s - rhs.s}; }
    void operator+=(const Node &rhs) { s += rhs.s; }

    static Node identity() { return Node{0}; }
};

struct Query {
    unsigned l, r, k;

    bool operator<(const Query &rhs) const {
        return tie(k, l, r) < tie(rhs.k, rhs.l, rhs.r);
    }
};

int main() {
    unsigned n;
    cin >> n;
    vector<Node> xs(n, {0});
    vector<pair<unsigned, unsigned>> ps(n);
    for (unsigned i = 0; i < n; i++) {
        cin >> ps[i].first;
        ps[i].second = i;
    }
    sort(ps.begin(), ps.end());

    unsigned q;
    cin >> q;
    vector<pair<Query, unsigned>> qs(q);
    for (unsigned i = 0; i < q; i++) {
        cin >> qs[i].first.l >> qs[i].first.r >> qs[i].first.k;
        qs[i].second = i;
    }
    sort(qs.begin(), qs.end());

    SegmentTree<Node> tree(xs);
    vector<unsigned> res(q);
    for (unsigned i = 0, j = 0; i < q; i++) {
        while (j < n && ps[j].first <= qs[i].first.k) {
            tree.update(ps[j++].second, {1});
        }
        unsigned l = qs[i].first.l - 1, r = qs[i].first.r - 1;
        res[qs[i].second] = 1 + r - l - tree.query(l, r).s;
    }

    for (unsigned i = 0; i < q; i++) {
        cout << res[i] << endl;
    }

    return 0;
}
