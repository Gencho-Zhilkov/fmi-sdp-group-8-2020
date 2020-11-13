/*
(0.75 т) Задача 1. Да се реализира метод void insertAtStart(x) за двойносвързания списък DList, който добавя елемент
със стойност x в началото на двойносвързан списък.
* Ако искате да използвате методи като insertAfter(p,x) и insertToEnd(x), трябва първо да ги дефинирате.
*/
#include <cassert>
#include <iostream>


template <typename T>
struct DNode {
    DNode<T> *prev;
    DNode<T> *next;
    T value;

    DNode(const T& value, DNode<T> *prev=nullptr, DNode<T> *next=nullptr):
        value(value), prev(prev), next(next) {}
};

template <typename T>
class DList {
// private:
public: // for easy testing below
    DNode<T> *head;
    DNode<T> *tail;

public:
    DList(): head(nullptr), tail(nullptr) {}

    void insertAtStart(const T& value) {
        if (head == nullptr) {
            assert(tail == nullptr);
            head = tail = new DNode<T>(value);
        } else {
            head = new DNode<T>(value, nullptr, head);
            head->next->prev = head;
        }
    }
};


int main() {
    using namespace std;

    DList<int> l;
    l.insertAtStart(1);
    l.insertAtStart(2);
    l.insertAtStart(3);
    for(auto p = l.head; p != nullptr; p = p->next) {
        cout << p->value << ' ';
    }
    cout << endl;

    return 0;
}
