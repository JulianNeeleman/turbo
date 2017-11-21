#include <iostream>
#include <vector>

#include "../../lib/structures/segment_tree.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

struct Node {
    unsigned l, r, t;
    bool cl, cr;

    Node operator*(const Node &rhs) const { return rhs; }

    static Node identity() { return {0, 0, 0, false, false}; }
};

int main() {
    string s;
    cin >> s;

    std::vector<Node> xs;
    for (char c : s) {
        bool p = (c == '(');
        xs.push_back(
            Node{static_cast<unsigned>(!p), static_cast<unsigned>(p), 0, p, p});
    }
    SegmentTree<Node> sg_tree(xs);

    unsigned m;
    cin >> m;
    for (unsigned i = 0; i < m; i++) {
        unsigned l, r;
        cin >> l >> r;
        cout << sg_tree.query(l, r).t << endl;
    }

    return 0;
}
