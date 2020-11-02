#include <iostream>
#include <functional>
#include <stack>
#include <stdexcept>
#include <string>


template <typename T> class RPNCalc {
private:
    std::stack<T> numbers;
    T current_number;
    bool parsing_number = false;

    void digit(const T& digit) {
        if (!parsing_number) {
            current_number = digit;
            parsing_number = true;
        } else {
            current_number = 10 * current_number + digit;
        }
    }

    void checkForEndOfNumber() {
        if (parsing_number) {
            numbers.push(current_number);
            parsing_number = false;
        }
    }

    template <typename Op> void op(const Op& op) {
        checkForEndOfNumber();
        if (numbers.size() < 2) {
            throw std::runtime_error("Not enough numbers to perform operation!");
        }
        const T& right = numbers.top();
        numbers.pop();
        const T& left = numbers.top();
        numbers.pop();
        numbers.push(op(left, right));
    }

    const T& result() {
        checkForEndOfNumber();
        if (numbers.size() != 1) {
            throw std::runtime_error("Invalid expression!");
        }
        return numbers.top();
    }

public:
    const T& eval(const std::string& line) {
        for(auto c: line) {
            if (c >= '0' && c <= '9') {
                digit(c - '0');
            } else if (c ==  ' ') {
                checkForEndOfNumber();
            } else if (c == '+') {
                op(std::plus());
            } else if (c == '-') {
                op(std::minus());
            } else if (c == '*') {
                op(std::multiplies());
            } else if (c == '/') {
                op(std::divides());
            } else {
                throw std::runtime_error("Invalid caracter!");
            }
        }
        return result();
    }
};


int main() {
    using namespace std;

    for(string line; getline(cin, line);) {
        try {
            auto c = RPNCalc<int>();
            cout << c.eval(line) << endl;
        } catch (runtime_error err) {
            cerr << err.what() << endl;
        }
    }
}
