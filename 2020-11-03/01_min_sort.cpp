#include <algorithm>
#include <iostream>
#include <vector>


template <typename It>
It findMin(const It& begin, const It& end) {
    auto min = begin;
    for(auto it = begin; it != end; ++it) {
        if(*it < *min) {
            min = it;
        }
    }
    return min;
}

template <typename It>
void minSort(const It& begin, const It& end) {
    for(auto start = begin; start != end; ++start) {
        auto min = findMin(start, end);
        std::iter_swap(start, min);
    }
}


int main() {
    using namespace std;

    vector<int> v = {1, 3, 5, 2, 7, 4, 8, 6};
    cout << *findMin(v.begin(), v.end()) << endl;

    minSort(v.begin(), v.end());
    for(auto x: v) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}
