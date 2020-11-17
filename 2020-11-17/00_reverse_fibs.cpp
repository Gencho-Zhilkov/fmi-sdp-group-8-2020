#include <iostream>
#include <stack>


template <typename T>
struct Node {
    T value;
    Node *next;

    Node(const T& value, Node *next=nullptr):
        value(value), next(next) {}
};

template <typename T>
bool isFib(const Node<T> *node) {
    if(node && node->next && node->next->next) {
        return node->next->next->value == node->value + node->next->value && isFib(node->next);
    } else {
        return true;
    }
}

template <typename T>
Node<T> *reverse(const Node<T> *node) {
    Node<T> *res = nullptr;
    for(auto current = node; current != nullptr; current = current->next) {
        res = new Node<T>(current->value, res);
    }
    return res;
}

template <typename T>
Node<T> *reverseFibs(const Node<T> *node) {
    if(isFib(node)) {
        return reverse(node);
    } else {
        return nullptr;
    }
}

template <typename T>
void print(const Node<T> *node) {
    if(node == nullptr) {
        std::cout << "Nothing!";
    } else {
        for(auto current = node; current != nullptr; current = current->next) {
            std::cout << current->value << ' ';
        }
    }
    std::cout << std::endl;
}

int main() {
    using namespace std;

    Node<int> *n = nullptr;
    print(reverseFibs(n));;
    print(reverseFibs(new Node(10)));;
    print(reverseFibs(new Node(10, new Node(20))));;
    print(reverseFibs(new Node(1, new Node(2, new Node(3)))));;
    print(reverseFibs(new Node(1, new Node(2, new Node(3, new Node(5, new Node(8)))))));;
    print(reverseFibs(new Node(1, new Node(2, new Node(3, new Node(6, new Node(8)))))));;
    print(reverseFibs(new Node(1, new Node(2, new Node(3, new Node(5, new Node(9)))))));;
}
