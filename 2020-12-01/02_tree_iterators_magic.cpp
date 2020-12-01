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


template <typename T, template<typename> typename It>
class TreeIteratorBase {
protected:
    Node<T> *current;

public:
    T& operator*() {
        return this->current->value;
    }

    bool operator==(const It<T>& that) const {
        return this->current == that.current;
    }

    bool operator!=(const It<T>& that) const {
        return !(*this == that);
    }
};

template <typename T>
class BfsIterator: public TreeIteratorBase<T, BfsIterator> {
private:
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
};

template <typename T>
class InOrderIterator: public TreeIteratorBase<T, InOrderIterator> {
private:
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
    for(auto x: tree1.bfs()) {
        cout << x << ' ';
    }
    cout << endl;

    //       4
    //    /     \
    //   2       6
    //  / \     / \
    // 1   3   5   7
    Tree<int> tree2(new Node(4,
        new Node(2, new Node(1), new Node(3)),
        new Node(6, new Node(5), new Node(7))
    ));
    for(auto x: tree2.inOrder()) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}
