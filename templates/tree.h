#include <cassert>
#include <stack>
#include <queue>


template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};

template <typename T, template <typename> typename It>
class TreeIterator {
protected:
    Node<T>* current;

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
class BfsIterator : public TreeIterator<T, BfsIterator> {
private:
    std::queue<Node<T>*> q;

public:
    BfsIterator(Node<T>* root) {
        if (root != nullptr) {
            q.push(root);
            ++(*this);
        } else {
            this->current = nullptr;
        }
    }

    BfsIterator& operator++() {
        if(!q.empty()) {
            this->current = q.front();
            q.pop();
            if(this->current->left) {
                q.push(this->current->left);
            }
            if(this->current->right) {
                q.push(this->current->right);
            }
        } else {
            this->current = nullptr;
        }
        return *this;
    }
};

template <typename T>
class InOrderIterator : public TreeIterator<T, InOrderIterator> {
// Ляво - Корен - Дясно
private:
    std::stack<Node<T>*> st;

    void push(Node<T>* node) {
        while(node)
        {
            st.push(node);
            node = node->left;
        }
    }

public:
    InOrderIterator(Node<T>* root) {
        push(root);
        ++(*this);
    }

    InOrderIterator& operator++() {
        if(st.empty())
        {
          this->current = nullptr;
        }
        else
        {
            this->current = st.top();
            st.pop();

            if(this->current->right)
            {
                push(this->current->right);
            }
        }

        return *this;
    }
};

template <typename T>
class BfsIteratorFactory {
private:
    Node<T> *root;

public:
    BfsIteratorFactory(Node<T> *root):
        root(root) {}

    BfsIterator<T> begin() {
        return BfsIterator<T>(root);
    }

    BfsIterator<T> end() {
        return BfsIterator<T>(nullptr);
    }
};

template <typename T>
class InOrderIteratorFactory {
private:
    Node<T> *root;

public:
    InOrderIteratorFactory(Node<T> *root):
        root(root) {}

    InOrderIterator<T> begin() {
        return InOrderIterator<T>(root);
    }

    InOrderIterator<T> end() {
        return InOrderIterator<T>(nullptr);
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

// TODO:
// PreOrderIterator<T>
// PostOrderIterator<T>

template <typename T>
class Tree {
private:
    Node<T> *root;

public:
    // TODO: ctors...
    // Dummy конструктор за тестове.
    Tree(Node<T> *root): root(root) {}

    BfsIterator<T> bfsBegin() {
        return BfsIterator<T>(root);
    }

    BfsIterator<T> bfsEnd() {
        return BfsIterator<T>(nullptr);
    }

    BfsIteratorFactory<T> bfs() {
        return BfsIteratorFactory<T>(this->root);
    }

    InOrderIteratorFactory<T> inOrder() {
        return InOrderIteratorFactory<T>(this->root);
    }

};
