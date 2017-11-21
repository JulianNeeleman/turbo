#include <iostream>
#include <vector>

#include "../../lib/structures/segment_tree.hpp"

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
