#include <iostream>
#include <list>

using namespace std;

/*
Каква е сложността на следната функция и защо?
*/
template <typename T>
list<T> merge(list<T> left, list<T> right) {
    list<T> res;
    auto li = left.begin(), ri = right.begin();
    while(li != left.end() && ri != right.end()) {
        if (*li <= *ri) {
            res.push_back(*li);
            ++li;
        } else {
            res.push_back(*ri);
            ++ri;
        }
    }
    for(; li != left.end(); ++li) {
        res.push_back(*li);
    }
    for(; ri != right.end(); ++ri) {
        res.push_back(*ri);
    }
    return res;
}


int main() {
    auto l1 = list<int> {1, 3, 5, 7};
    auto l2 = list<int> {2, 4, 6, 8};
    for(auto x: merge(l1, l2)) {
        cout << x << endl;
    }
}
