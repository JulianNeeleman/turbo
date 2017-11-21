#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

#include "../../lib/structures/segment_tree.hpp"

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
