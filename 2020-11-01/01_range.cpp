#include <iostream>


template <typename T=int>
class range {
private:
    T start, stop;

public:
    class iterator {
    private:
        T current;

    public:
        iterator(const T& current):
            current(current) {}

        T operator*() {
            return current;
        }

        iterator& operator++() {
            ++current;
            return *this;
        }

        bool operator==(const iterator& that) const {
            return current == that.current;
        }

        bool operator!=(const iterator& that) const {
            return !(*this == that);
        }
    };

    range(const T& start, const T& stop):
        start(start), stop(stop) {}

    iterator begin() {
        return iterator(start);
    }

    iterator end() {
        return iterator(stop);
    }
};


int main() {
    using namespace std;

    // Искаме да превърнем този for-цикъл в итератор
    for(auto i = 3; i != 10; ++i) {
        cout << i << endl;
    }
    cout << endl << endl;
    // и да го накараме да изглежда по този начин
    for(auto i: range(3, 10)) {
        cout << i << endl;
    }
    cout << endl << endl;
    // което е същото като:
    auto r = range(3, 10);
    for(auto it = r.begin(); it != r.end(); ++it) {
        const auto i = *it;
        cout << i << endl;
    }

    return 0;
}
