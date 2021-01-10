#include <iostream>


// Ex 1. subtree
template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};

template <typename T>
bool equals(const Node<T> *tree, const Node<T> *sub) {
  if (sub==nullptr || tree == nullptr) {
    return tree == sub;
  }

  return tree->value == sub->value && equals(tree->left, sub->left) && equals(tree->right, sub->right);
}

template <typename T>
bool subtree(const Node<T> *tree, const Node<T> *sub) {
    if (equals(tree, sub)) {
        return true;
    }
    if (tree == nullptr) {
        return false;
    }
    return subtree(tree->left, sub) || subtree(tree->right,sub);
}

int main() {
    using namespace std;

    auto large = new Node(1,
        new Node(2, new Node(3)),
        new Node(4, new Node(5), new Node(6))
    );

    auto small = new Node(4, new Node(5), new Node(6));

    cout << subtree(large, small) << endl;
    cout << subtree(small, large) << endl;
}
