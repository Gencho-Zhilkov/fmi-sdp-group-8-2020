#include <cassert>
#include <iostream>
#include <numeric>
#include <stack>
#include <string>


unsigned factorial(unsigned n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}

unsigned to_digit(char c) {
    return c - '0';
}

template <typename T>
T get_and_pop(std::stack<T>& stack) {
    assert(stack.size() > 0);
    auto res = stack.top();
    stack.pop();
    return res;
}

/*
израз = неотрицателно цяло число | f(израз) | g(израз) | m(израз,израз), където:
● f(x) = (x * x) mod 100, където mod 100 връща остатъка при деление на 100
● g(x) = (x mod 5)! , т.е. факториелът на остатъка на деленето на х на 5
● m(x,y) = min(x,y)
*/
unsigned evaluate(std::string expression) {
    std::stack<unsigned> numbers;
    std::stack<char> ops;

    bool expect_open_bracket = false;
    bool last_is_digit = false;
    unsigned current_number = 0;

    for(auto c: expression) {
        assert((c == '(') == expect_open_bracket);
        expect_open_bracket = false;

        if (c == 'f' || c == 'g' || c == 'm') {
            ops.push(c);
            expect_open_bracket = true;
        } else if (c >= '0' && c <= '9') {
            last_is_digit = true;
            current_number = 10 * current_number + to_digit(c);
        } else if (c == ',') {
            if (last_is_digit) {
                numbers.push(current_number);
                current_number = 0;
                last_is_digit = false;
            }
        } else if (c == ')') {
            if (last_is_digit) {
                numbers.push(current_number);
                current_number = 0;
                last_is_digit = false;
            }

            auto op = get_and_pop(ops);
            if (op == 'f') {
                auto x = get_and_pop(numbers);
                numbers.push((x * x) % 100);
            } else if (op == 'g') {
                auto x = get_and_pop(numbers);
                numbers.push(factorial(x % 5));
            } else {
                assert(op == 'm');
                auto x = get_and_pop(numbers);
                auto y = get_and_pop(numbers);
                numbers.push(std::min(x, y));
            }
        } else {
            // skip everything else: we may want to add some validation later
        }
    }

    if (last_is_digit) {
        numbers.push(current_number);
    }

    assert(numbers.size() == 1);
    return numbers.top();
}

int main() {
    using namespace std;

    cout << evaluate("1234") << endl;
    cout << evaluate("f(15)") << endl;
    cout << evaluate("m(f(15),24)") << endl;
    cout << evaluate("f(m(25,g(14)))") << endl;
    cout << evaluate("m(m(23,15),18)") << endl;
    cout << evaluate("m(m(m(m(m(1,2),3),4),5),6)") << endl;

    return 0;
}
