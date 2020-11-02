#include <iostream>


template <typename T>
struct Node {
    T value;
    Node *next;

    Node(const T& value, Node *next=nullptr):
        value(value), next(next) {}
};

template <typename T>
bool find(const T& value, const Node<T> *start, const Node<T> *end) {
    for(auto node = start; node != end; node = node->next) {
        if (node->value == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
void dedup(Node<T> *head) {
    Node<T> *prev = nullptr, *node = head;
    while(node != nullptr) {
        if (find(node->value, head, node)) {
            // unlink node from the list and delete it
            prev->next = node->next;
            delete node;
        } else {
            // move prev forward
            prev = node;
        }
        // move node forward
        node = prev->next;
    }
}


int main() {
    using namespace std;

    Node<int> *head = nullptr;
    for(auto i: {1, 2, 3, 7, 2, 1, 5, 3}) {
        head = new Node<int>(i, head);
    }

    dedup(head);

    for(auto current = head; current != nullptr; current = current->next) {
        cout << current->value << endl;
    }

    return 0;
}
