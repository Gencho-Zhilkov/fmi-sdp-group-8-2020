#include <algorithm>
#include <iostream>
#include <functional>


template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};


// Брой елементи на дървото
template <typename T>
size_t size(const Node<T> *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return size(root->left) + size(root->right) + 1;
    }
}

// Височина на дървото
template <typename T>
size_t height(const Node<T> *root) {
  if(root==nullptr)
    return 0;
  return 1 + std::max(height(root->left), height(root->right));
}


/*** ОБХОЖДАНИЯ ***/
// Корен - Ляво - Дясно
template <typename T>
void walkPreOrder(Node<T> *root, void (*callback)(Node<T> *node)) {
    if(root != nullptr) {
        callback(root);
        walkPreOrder(root->left, callback);
        walkPreOrder(root->right, callback);
    }
}

// Ляво - Корен - Дясно
template <typename T>
void walkInOrder(Node<T> *root, void (*callback)(Node<T> *node)) {
    if(root != nullptr) {
        walkInOrder(root->left, callback);
        callback(root);
        walkInOrder(root->right, callback);
    }
}

// Ляво - Дясно - Корен
template <typename T>
void walkPostOrder(Node<T> *root, void (*callback)(Node<T> *node)) {
    if(root != nullptr) {
        walkPostOrder(root->left, callback);
        walkPostOrder(root->right, callback);
        callback(root);
    }
}


// Огледален образ
template <typename T>
void swap(Node<T> *node) {
    std::swap(node->left, node->right);
}

template <typename T>
void mirror(Node<T> *root) {
    walkPreOrder(root, swap<T>);
}

template <typename T>
void print(Node<T>* node) {
    std::cout << node->value << ' ';
}

int main() {
    using namespace std;

    // Брой елементи + Височина
    const Node<int> *t1 = nullptr;
    const Node<int> *t2 = new Node(1);
    const Node<int> *t3 = new Node(1, new Node(2), new Node(3));
    const Node<int> *t4 = new Node(1, new Node(2, new Node(3)), new Node(4));

    for(auto t: {t1, t2, t3, t4}) {
        cout << size(t) << ' ';
    }
    cout << endl;

    for(auto t: {t1, t2, t3, t4}) {
        cout << height(t) << ' ';
    }
    cout << endl;

    // Обхождания
    Node<int> *t = new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    );

    cout << "Pre-order: ";
    walkPreOrder(t, print);  // 1 2 4 5 3 6 7
    cout << endl;

    cout << "In-order: ";
    walkInOrder(t, print);   // 4 2 5 1 6 3 7
    cout << endl;

    cout << "Post-order: ";
    walkPostOrder(t, print); // 4 5 2 6 7 3 1
    cout << endl;

    cout << "Mirrored: ";
    mirror(t);
    walkPreOrder(t, print);
    cout << endl;

    return 0;
}
