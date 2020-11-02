#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


/*
Въпроси:
1. Каква е сложността на функцията intersect() ?
2. Как бихме могли да оптимизираме това, имайки предвид, че двата вектора са сортирани ?
*/
template<typename T>
vector<T> intersect(vector<T> left, vector<T> right) {
    vector<T> res;
    for(auto x: left) {
        if (find(right.begin(), right.end(), x) != right.end()) {
            res.push_back(x);
        }
    }
    return res;
}

int main() {
    auto l1 = vector<int> {1, 2, 3, 5, 7};
    auto l2 = vector<int> {2, 4, 5, 6, 8};
    for(auto x: intersect(l1, l2)) {
        cout << x << endl;
    }
}

