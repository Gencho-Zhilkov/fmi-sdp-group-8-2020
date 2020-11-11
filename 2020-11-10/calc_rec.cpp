#include <cassert>
#include <iostream>
#include <string>


unsigned factorial(unsigned n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}

size_t commaPosition(std::string expression) {
  int bracketCounter = 0;
  for(auto i = 0; i < expression.size(); i++) {
    auto c = expression[i];
    if (c == '(') {
      bracketCounter++;
    } else if (c == ')') {
      bracketCounter--;
    } else if (c == ',' && bracketCounter == 0) {
      return i;
    }
  }
  assert(false); // "Invalid expression"
}

/*
израз = неотрицателно цяло число | f(израз) | g(израз) | m(израз,израз), където:
● f(x) = (x * x) mod 100, където mod 100 връща остатъка при деление на 100
● g(x) = (x mod 5)! , т.е. факториелът на остатъка на деленето на х на 5
● m(x,y) = min(x,y)
*/
int evaluate(std::string expression) {
    // std::cout << expression << std::endl;
    assert(expression.size() > 0);

    if(expression[0] == 'f') {
        assert(expression[1] == '(');
        assert(expression.back() == ')');
        auto x = evaluate(expression.substr(2, expression.size() - 3));
        return (x * x) % 100;
    } else if (expression[0] == 'g') {
        assert(expression[1] == '(');
        assert(expression.back() == ')');
        auto x = evaluate(expression.substr(2, expression.size() - 3));
        return factorial(x % 5);
    } else if (expression[0] == 'm') {
        assert(expression[1] == '(');
        assert(expression.back() == ')');

        auto temp = expression.substr(2, expression.size() - 3);
        unsigned pos = commaPosition(temp);
        auto x = evaluate(temp.substr(0, pos));
        auto y = evaluate(temp.substr(pos+1, temp.size() - pos - 1));
        return std::min(x, y);
    } else {
        // Изразът е число
        return stoi(expression);
    }
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
