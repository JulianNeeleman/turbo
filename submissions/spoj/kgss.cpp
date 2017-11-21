#include <iostream>
#include <vector>

#include "../../lib/structures/segment_tree.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct Node {
    unsigned t, m;

    Node operator*(const Node &rhs) const {
        return Node{max(m + rhs.m, max(t, rhs.t)), max(m, rhs.m)};
    }

    Node operator-(const Node &rhs) const { return Node{}; }
    void operator+=(const Node &rhs) { t += rhs.t; }

    static Node identity() { return {0, 0}; }
};

int main() {
    unsigned n;
    cin >> n;

    vector<Node> xs(n);
    for (unsigned i = 0; i < n; i++) {
        unsigned v;
        cin >> v;
        xs[i] = Node{v, v};
    }
    SegmentTree<Node> tree(xs);

    unsigned q;
    cin >> q;
    for (unsigned i = 0; i < q; i++) {
        char ch;
        unsigned a, b;
        cin >> ch >> a >> b;
        if (ch == 'Q') {
            cout << tree.query(a - 1, b - 1).m << endl;
        } else {
        }
    }
    return 0;
}
