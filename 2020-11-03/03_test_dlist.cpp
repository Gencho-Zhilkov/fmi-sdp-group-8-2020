#include <iostream>
#include "../templates/dlist.h"


using namespace std;

template<typename T>
void printList(const DList<T>& l) {
    for(auto val: l) {
        cout << val << ' ';
    }
    cout << endl;
}

int main() {
    DList<int> l;
    l.insertBefore(l.begin(), 5);
    l.insertHead(3);
    l.insertAfter(l.begin(), 7);
    printList(l);

    DList<int> l2 = {1, 2, 3, 4};
    l = l2;
    printList(l);

    auto it = l.begin();
    ++it;
    ++it;

    l.insertBefore(it, 10);
    l.insertAfter(it, 20);
    printList(l);

    l.removeAfter(it);
    l.removeBefore(it);
    l.removeAt(it);
    printList(l);
    return 0;
}
