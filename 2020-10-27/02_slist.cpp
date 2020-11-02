#include <iostream>
#include "../templates/slist.h"

int main() {
    using namespace std;

    SList<int> l = {1, 2, 3, 4, 5};
    auto l2(l);
    l = l2;

    cout << "Before: " << (l == l2) << endl;
    for(auto it = l.begin(); it != l.end(); ++it) {
        if (*it % 2 == 0) {
            l.insertAfter(it, 7);
        }
    }
    cout << "After: " << (l == l2) << endl;

    for(auto i: l) {
        cout << i << endl;
    }

    return 0;
}
