#include <cassert>
#include <climits>
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <stack>


struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int data, Node *left=nullptr, Node *right=nullptr):
        data(data), left(left), right(right) {}
};

// Ex. 1
// Return INT_MIN if tree is empty or there are no increasing paths from root to any leaf.
int maxpathHelper(Node *node) {
    assert(node != nullptr);

    if (node->left == nullptr && node->right == nullptr) {
        return node->data; // leaf node
    }

    int res = INT_MIN;
    if (node->left != nullptr && node->left->data > node->data) {
        res = maxpathHelper(node->left);
    }
    if (node->right != nullptr && node->right->data > node->data) {
        res = std::max(res, maxpathHelper(node->right));
    }

    if (res != INT_MIN) {
        res += node->data;
    }
    return res;
}

int maxpath(Node *root) {
    if (root == nullptr) {
        return INT_MIN;
    }
    return maxpathHelper(root);
}

// Ex. 2
std::vector<int> rightlook(Node *root) {
    std::vector<int> res;

    if(root != nullptr) {
        std::vector<Node *> nodes({root});
        while(!nodes.empty()) {
            std::vector<Node *> newNodes;
            res.push_back(nodes.back()->data);
            for(auto node: nodes) {
                if (node->left != nullptr) {
                    newNodes.push_back(node->left);
                }
                if (node->right != nullptr) {
                    newNodes.push_back(node->right);
                }
            }
            nodes = newNodes;
        }
    }

    return res;
}

// Ex. 3
struct GNode {
    int value;
    std::unordered_set<size_t> neighbours;
};

class Graph {
private:
    std::vector<GNode> nodes;

public:
    Graph(std::vector<int> values): nodes(values.size()) {
        for (auto i = 0; i < values.size(); i++) {
            nodes[i].value = values[i];
        }
    }

    void addEdge(size_t i, size_t j) {
        i -= 1; j -= 1; // Node indexes are 1-based ...
        nodes[i].neighbours.insert(j);
        nodes[j].neighbours.insert(i);
    }

    int minSum() const {
        int res = 0;
        std::unordered_set<size_t> visited;
        for (auto i = 0; i < nodes.size(); i++) {
            if (visited.find(i) != visited.end())
                continue; // already handled in some previous CC

            std::stack<size_t> st;
            st.push(i);
            visited.insert(i);
            int minVal = nodes[i].value;

            while(!st.empty()) {
                auto nodeId = st.top();
                st.pop();

                for(auto nb: nodes[nodeId].neighbours) {
                    if (visited.find(nb) != visited.end())
                        continue;

                    if (nodes[nb].value < minVal) {
                        minVal = nodes[nb].value;
                    }

                    st.push(nb);
                    visited.insert(nb);
                }
            }

            res += minVal;
        }

        return res;
    }
};


int main() {
    using namespace std;

    // Ex. 1
    auto n1 = new Node(1,
        new Node(2, new Node(3)),
        new Node(1, new Node(9), new Node(8))
    );
    cout << maxpath(n1) << endl;

    // Ex. 2
    auto n2 = new Node(1,
        new Node(2, nullptr, new Node(5)),
        new Node(3)
    );
    for (auto v: rightlook(n2)) {
        cout << v << ' ';
    }
    cout << endl;

    // Ex. 3
    auto g1 = Graph({10, 60, 20, 70, 30, 80, 40, 90, 50, 100});
    g1.addEdge(1, 2);
    g1.addEdge(3, 4);
    g1.addEdge(5, 6);
    g1.addEdge(7, 8);
    g1.addEdge(9, 10);
    cout << g1.minSum() << endl;

    auto g2 = Graph({20, 50, 30, 40, 80});
    g2.addEdge(1, 4);
    g2.addEdge(4, 5);
    cout << g2.minSum() << endl;

    return 0;
}
