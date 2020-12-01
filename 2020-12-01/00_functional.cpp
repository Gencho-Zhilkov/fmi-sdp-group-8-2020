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

// Корен - Ляво - Дясно
template <typename T, typename C=void>
// void walkPreOrder(Node<T> *root, void (*callback)(Node<T>*)) {
// void walkPreOrder(Node<T> *root, std::function<void(Node<T>*)> callback) {
void walkPreOrder(Node<T> *root, C&& callback) {
    if(root != nullptr) {
        callback(root);
        walkPreOrder<T>(root->left, callback);
        walkPreOrder<T>(root->right, callback);
    }
}


// Брой елементи: директна имплементация
template <typename T>
size_t size(const Node<T> *root) {
    return root == nullptr ? 0 : 1 + size(root->left) + size(root->right);
}


// Указател към ф-я + глобална променлива
size_t res = 0;

template<typename T>
void inc(Node<T> *node) {
    res ++;
}

template<typename T>
size_t size_fptr(Node<T> *root) {
    res = 0;
    walkPreOrder<T>(root, inc<T>);
    return res;
}

// Иначе трябва да променим колбеците на нещо от сорта на:
template<typename T, typename State>
void callback(State& state, Node<T> *node) {}


// OOP-style
template<typename T>
struct Counter {
    size_t count = 0;

    void operator()(/*Counter *this, */ Node<T> *node) {
        count ++;
    }
};

template<typename T>
size_t size_counter(Node<T> *root) {
    Counter<T> c;
    walkPreOrder<T>(root, c);
    return c.count;
}


// FP-(ish)-style
template<typename T>
size_t size_lambda(Node<T> *root) {
    size_t res = 0;
    walkPreOrder<T>(root, [&res](Node<T> *_) { res++; });
    return res;
}


int main() {
    using namespace std;

    Node<int> *t = new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    );

    cout << size(t) << endl;
    cout << size_fptr(t) << endl;
    cout << size_counter(t) << endl;
    cout << size_lambda(t) << endl;
}
