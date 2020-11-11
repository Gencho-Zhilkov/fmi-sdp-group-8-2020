/*
израз = неотрицателно цяло число | f(израз) | g(израз) | m(израз,израз), където:
● f(x) = (x * x) mod 100, където mod 100 връща остатъка при деление на 100
● g(x) = (x mod 5)! , т.е. факториелът на остатъка на деленето на х на 5
● m(x,y) = min(x,y)
*/
#include <cassert>
#include <iostream>
#include <map>
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


struct Op {
    virtual void eval(std::stack<unsigned>& args) = 0;
};

struct F: public Op {
    virtual void eval(std::stack<unsigned>& args) {
        auto x = get_and_pop(args);
        args.push((x * x) % 100);
    }
};

struct G: public Op {
    virtual void eval(std::stack<unsigned>& args) {
        auto x = get_and_pop(args);
        args.push(factorial(x % 5));
    }
};

struct M: public Op {
    virtual void eval(std::stack<unsigned>& args) {
        auto x = get_and_pop(args);
        auto y = get_and_pop(args);
        args.push(std::min(x, y));
    }
};


class Calc {
private:
    static std::map<char, Op*> fmap;

    std::stack<unsigned> numbers;
    std::stack<Op*> ops;

    bool expect_open_bracket = false;
    bool last_is_digit = false;
    unsigned current_number = 0;

public:
    Calc(): numbers(), ops() {}

    void check_push_number() {
        if (last_is_digit) {
            numbers.push(current_number);
            current_number = 0;
            last_is_digit = false;
        }
    }

    unsigned evaluate(std::string expression);
};

std::map<char, Op*> Calc::fmap = {
    {'f', new F()},
    {'g', new G()},
    {'m', new M()},
};

unsigned Calc::evaluate(std::string expression) {
    for(auto c: expression) {
        assert((c == '(') == expect_open_bracket);
        expect_open_bracket = false;

        auto it = fmap.find(c);
        if (it != fmap.end()) {
            ops.push(it->second);
            expect_open_bracket = true;
        } else if (c >= '0' && c <= '9') {
            last_is_digit = true;
            current_number = 10 * current_number + to_digit(c);
        } else if (c == ',') {
            check_push_number();
        } else if (c == ')') {
            check_push_number();

            auto op = get_and_pop(ops);
            op->eval(numbers);
        } else {
            // skip everything else: we may want to add some validation later
        }
    }

    check_push_number();
    assert(numbers.size() == 1);
    return get_and_pop(numbers);
}

int main() {
    using namespace std;

    Calc calc;

    cout << calc.evaluate("1234") << endl;
    cout << calc.evaluate("f(15)") << endl;
    cout << calc.evaluate("m(f(15),24)") << endl;
    cout << calc.evaluate("f(m(25,g(14)))") << endl;
    cout << calc.evaluate("m(m(23,15),18)") << endl;
    cout << calc.evaluate("m(m(m(m(m(1,2),3),4),5),6)") << endl;

    return 0;
}
