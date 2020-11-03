#include <algorithm>
#include <iostream>
#include <vector>


template <typename It>
void insertionSort(const It& begin, const It& end) {
    for(auto current = begin; current != end; ++current) {
        for(auto it = begin; it != current; ++it) {
            if(*current < *it) {
                std::swap(*current, *it);
            }
        }
    }
}


int main() {
    using namespace std;

    vector<int> v1 = {};
    vector<int> v2 = {1};
    vector<int> v3 = {1, 2, 3, 4};
    vector<int> v4 = {4, 3, 2, 1};
    vector<int> v5 = {1, 3, 5, 2, 7, 4, 8, 6};
    vector<int> v6 = {1, 2, 5, 2, 7, 4, 6, 5};

    for(auto v: {v1, v2, v3, v4, v5, v6}) {
        insertionSort(v.begin(), v.end());
        for(auto x: v) {
            cout << x << ' ';
        }
        cout << endl;
    }

    return 0;
}
