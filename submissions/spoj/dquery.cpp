#include <iostream>
#include <set>
#include <vector>

#include "../../lib/structures/segment_tree.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;

struct Node {
    set<unsigned> s;

    Node operator*(const Node &rhs) const {
        Node prod = Node{{s}};
        prod.s.insert(rhs.s.begin(), rhs.s.end());
        return prod;
    }

    static Node identity() { return {{}}; }
};

int main() {
    unsigned n;
    cin >> n;

    vector<Node> xs(n);
    for (unsigned i = 0; i < n; i++) {
        unsigned v;
        cin >> v;
        xs[i] = Node{{v}};
    }
    SegmentTree<Node> tree(xs);

    unsigned q;
    cin >> q;
    for (unsigned i = 0; i < q; i++) {
        unsigned l, r;
        cin >> l >> r;
        cout << tree.query(l - 1, r - 1).s.size() << endl;
    }
    return 0;
}
