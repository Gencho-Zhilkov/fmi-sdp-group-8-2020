#include <cassert>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>


template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};

// Дефинирайте функцята findPath(tree, sum), която приема
// двоично дърво от цели числа tree и целочислена стойност sum
// и връща път започващ от корена на дървото, за койте сумата
// на стойностите на върхувете му е равна на sum
std::list<int> findPath(Node<int>* tree, int sum) {
    // В случая предполагаме, че всички стойности са положителни.
    if (tree == nullptr || sum < tree->value) {
        return std::list<int>();
    }
    if (tree->value == sum) {
        return std::list<int>({sum});
    }

    std::list<int> result = findPath(tree->left, sum - tree->value);
    if (result.empty()) {
        result = findPath(tree->right, sum- tree->value);
    }

    if (!result.empty()) {
        result.push_front(tree->value);
    }
    return result;
}

// Итеративно решение, стойностите може да са положителни и отрицателни
std::list<int> findPath_iter(const Node<int>* tree, int sum) {
    std::list<int> res;
    std::stack<std::queue<const Node<int>*>> st;
    auto remaining = sum;

    if(tree != nullptr) {
        st.push(std::queue<const Node<int>*>({tree}));
    }

    while (!st.empty()) {
        auto& q = st.top();

        if (q.empty()) { // back-track
            st.pop();

            if (!res.empty()) { // Empty when poping the _root_ queue (path not found)
                remaining += res.back();
                res.pop_back();
            }
        } else {
            auto n = q.front();
            q.pop();

            res.push_back(n->value);
            remaining -= n->value;

            if (remaining == 0) {
                return res;
            } else {
                auto next = std::queue<const Node<int>*>();
                if(n->left != nullptr) {
                    next.push(n->left);
                }
                if(n->right != nullptr) {
                    next.push(n->right);
                }
                st.push(next);
            }
        }
    }

    // Nothing found => res MUST be empty!
    assert(res.empty());
    return res;
}

int main() {
    using namespace std;

    //       1
    //    /     \
    //   2       3
    //  / \     / \
    // 4   5   6   7
    Node<int> *tree = new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    );

    cout << "Recursive:" << endl;
    for(auto sum: {3, 6, 8, 11, 15}) {
      auto path = findPath(tree, sum);
      cout << sum << " -> [";
      for (auto v: path) {
          cout << v << ' ';
      }
      cout << "]" << endl;
    }
    cout << endl;

    cout << "Iterative:" << endl;
    for(auto sum: {3, 6, 8, 11, 15}) {
      auto path = findPath_iter(tree, sum);
      cout << sum << " -> [";
      for (auto v: path) {
          cout << v << ' ';
      }
      cout << "]" << endl;
    }
    cout << endl;

    return 0;
}
