#include <cassert>
#include <iostream>


template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};


// Дефинирайте функцята sumLeaves(tree), която приема
// двоично дърво от цели числа tree и връща сумата от
// листата му.
template <typename T>
bool isLeaf(const Node<T> *node) {
    assert(node != nullptr);
    return node->left == nullptr && node->right == nullptr;
}

template <typename T=int>
T sumLeaves(Node<T>* node) {
  if(node == nullptr) {
    return T();
  } else if(isLeaf(node)) {
    return node->value;
  } else {
    return sumLeaves(node->left) + sumLeaves(node->right);
  }
}


int main() {
    using namespace std;

    //       1
    //    /     \
    //   2       3
    //  / \     / \
    // 4   5   6   7
    auto tree1 = new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    );

    //       4
    //    /     \
    //   2       6
    //  / \     / \
    // 1   3   5   7
    auto tree2 = new Node(4,
        new Node(2, new Node(1), new Node(3)),
        new Node(6, new Node(5), new Node(7))
    );

    cout << sumLeaves<int>(nullptr) << endl;
    cout << sumLeaves(tree1) << endl;
    cout << sumLeaves(tree2) << endl;

    return 0;
}
