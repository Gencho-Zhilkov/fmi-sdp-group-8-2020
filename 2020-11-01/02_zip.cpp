#include <iostream>
#include <vector>
#include <string>
#include <tuple>


template <typename U, typename V>
class zip {
private:
    U u;
    V v;

public:
    class iterator {
    private:
        friend class zip;

        typedef typename U::iterator UIt;
        typedef typename V::iterator VIt;

        UIt uit, uend;
        VIt vit, vend;

        iterator(UIt uit, UIt uend, VIt vit, VIt vend):
            uit(uit), uend(uend), vit(vit), vend(vend) {}

    public:
        std::tuple<typename U::value_type, typename V::value_type> operator*() {
            return std::tuple(*uit, *vit);
        }

        iterator& operator++() {
            ++uit;
            ++vit;
            return *this;
        }

        bool operator==(const iterator& that) const {
            if(uit == uend) {
                return that.uit == uend;
            } else if (vit == vend) {
                return that.vit == vend;
            } else {
                return uit == that.uit && vit == that.vit;
            }
        }

        bool operator!=(const iterator& that) const {
            return !(*this == that);
        }
    };

    zip(const U& u, const V& v):
        u(u), v(v) {}

    iterator begin() {
        return iterator(u.begin(), u.end(), v.begin(), v.end());
    }

    iterator end() {
        return iterator(u.end(), u.end(), v.end(), v.end());
    }
};


int main(int argc, char const *argv[]) {
    using namespace std;

    string s = "foobarbazbam";
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for(auto [c, i]: zip(s, v)) {
        cout << c << ", " << i << endl;
    }
    return 0;
}
