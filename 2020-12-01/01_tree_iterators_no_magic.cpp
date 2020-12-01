#include <cassert>
#include <stack>
#include <queue>
#include <iostream>


template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};


template <typename T>
class BfsIterator {
private:
    Node<T> *current;
    std::queue<Node<T>*> q;

    void push(Node<T> *node) {
        if (node != nullptr) {
            q.push(node);
        }
    }

public:
    BfsIterator(Node<T> *node) {
        push(node);
        ++(*this);
    }

    BfsIterator& operator++() {
        if (!q.empty()) {
            this->current = q.front();
            q.pop();
            push(this->current->left);
            push(this->current->right);
        } else {
            this->current = nullptr;
        }

        return *this;
    }

    T& operator*() {
        return this->current->value;
    }

    bool operator==(const BfsIterator<T>& that) const {
        return this->current == that.current;
    }

    bool operator!=(const BfsIterator<T>& that) const {
        return !(*this == that);
    }
};

template <typename T>
class InOrderIterator {
private:
    Node<T> *current;
    std::stack<Node<T>*> st;

    void push(Node<T> *node) {
        while(node != nullptr) {
            st.push(node);
            node = node->left;
        }
    }

public:
    InOrderIterator(Node<T> *node) {
        push(node);
        ++(*this);
    }

    InOrderIterator& operator++() {
        if (st.empty()) {
            this->current = nullptr;
        } else {
            this->current = st.top();
            st.pop();
            push(this->current->right);
        }
        return *this;
    }

    T& operator*() {
        return this->current->value;
    }

    bool operator==(const InOrderIterator<T>& that) const {
        return this->current == that.current;
    }

    bool operator!=(const InOrderIterator<T>& that) const {
        return !(*this == that);
    }
};


template <typename T, template<typename> typename It>
class IteratorFactory {
private:
    Node<T> *root;

public:
    IteratorFactory(Node<T> *root):
        root(root) {}

    It<T> begin() {
        return It<T>(root);
    }

    It<T> end() {
        return It<T>(nullptr);
    }
};

template <typename T>
class Tree {
private:
    Node<T> *root;

public:
    // TODO: ctors...
    // Dummy конструктор за тестове.
    Tree(Node<T> *root): root(root) {}

    IteratorFactory<T, BfsIterator> bfs() {
        return IteratorFactory<T, BfsIterator>(this->root);
    }

    IteratorFactory<T, InOrderIterator> inOrder() {
        return IteratorFactory<T, InOrderIterator>(this->root);
    }

    // Може и директно с различни begin/end методи за всеки тип итератор:
    BfsIterator<T> bfsBegin() {
        return BfsIterator<T>(root);
    }

    BfsIterator<T> bfsEnd() {
        return BfsIterator<T>(nullptr);
    }

    InOrderIterator<T> inOrderBegin() {
        return InOrderIterator<T>(root);
    }

    InOrderIterator<T> inOrderEnd() {
        return InOrderIterator<T>(nullptr);
    }

};


int main() {
    using namespace std;

    //       1
    //    /     \
    //   2       3
    //  / \     / \
    // 4   5   6   7
    Tree<int> tree1(new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    ));

    //       4
    //    /     \
    //   2       6
    //  / \     / \
    // 1   3   5   7
    Tree<int> tree2(new Node(4,
        new Node(2, new Node(1), new Node(3)),
        new Node(6, new Node(5), new Node(7))
    ));

    // Foreach-style обхождания с IteratorFactory методите
    for(auto x: tree1.bfs()) {
        cout << x << ' ';
    }
    cout << endl;

    for(auto x: tree2.inOrder()) {
        cout << x << ' ';
    }
    cout << endl;

    // Обхождания, ако не искаме да използваме IteratorFactory методите
    for(auto it = tree1.bfsBegin(); it != tree1.bfsEnd(); ++it) {
        cout << *it << '-';
    }
    cout << endl;

    for(auto it = tree2.inOrderBegin(); it != tree2.inOrderEnd(); ++it) {
        cout << *it << '-';
    }
    cout << endl;

    return 0;
}
