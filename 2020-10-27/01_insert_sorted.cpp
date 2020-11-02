#include <iostream>

template <typename T>
struct Node {
    Node *next;
    T value;

    Node(const T& value, Node *next=nullptr):
        value(value), next(next) {}
};


/*
Нека head е указател към главата на едносвързан списък, в който елементите вече са сортирани в нарастващ ред, т.е. head->value <= head->next->value <= ...
Дефинирайте void insertSortded(Node<T>*& head, const T& value) добавя value в този списък, като запазва подредеността на списъка.
*/
template <typename T>
void insertSorted(Node<T>*& head, const T& value) {
    if(head == nullptr || value < head->value) {
        head = new Node<T>(value, head);
    } else {
        insertSorted(head->next, value);
    }
}


int main() {
    using namespace std;

    Node<int> *head = nullptr;
    for(auto i: {7, 5, 3, 1}) {
        head = new Node<int>(i, head);
    }

    insertSorted(head, 4);
    insertSorted(head, 6);
    insertSorted(head, 2);
    insertSorted(head, 8);
    insertSorted(head, 0);

    for(auto current = head; current != nullptr; current = current->next) {
        cout << current->value << endl;
    }

    return 0;
}
