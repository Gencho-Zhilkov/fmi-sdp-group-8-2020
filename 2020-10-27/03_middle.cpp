#include <iostream>
#include "../templates/slist.h"


template <typename It>
bool moveTwice(It& it, const It& end) {
    for(size_t i = 0; i < 2; ++i, ++it) {
        if (it == end) {
            return false;
        }
    }
    return true;
}

template <typename T>
typename SList<T>::iterator middle(SList<T>& l) {
    auto slow = l.begin(), fast = l.begin();
    while (moveTwice(fast, l.end())) {
        ++slow;
    }
    return slow;
}


int main() {
    using namespace std;

    SList<int> l1 = {1, 3, 5, 7};
    SList<int> l2 = {2, 4, 6, 8, 10};

    cout << *middle(l1) << endl;
    cout << *middle(l2) << endl;

    return 0;
}
