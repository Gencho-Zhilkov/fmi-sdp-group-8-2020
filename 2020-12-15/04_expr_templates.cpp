#include <iostream>
#include <functional>

/*
Аритметични изрази:
Нека имаме аритметични изрази състоящи се от:
- числа
- двоични оператори: +, *, -, /
Можем да ги представим като двоични дървета.
Примери:
  (3 + 5) * (7 - 2)
          *
      //     \\
     +        -
   // \\    // \\
   3   5    7   2


    12 / (3 + 1)
       /
    //   \\
   12     +
        // \\
        3   1

Дефинирайте функция eval(expr), която приема двоично дърво
съответстващо на даден аритметичен израз и връща стойността
на дадения израз.
*/

class Expression {
public:
    virtual int eval() const = 0;
};

class Value: public Expression {
private:
    int value;

public:
    Value(const int value): value(value) {}

    int eval() const {
        return value;
    }
};

template <template <typename> typename Op>
class BinOp: public Expression {
protected:
    Expression *lhs;
    Expression *rhs;

public:
    BinOp(Expression *lhs, Expression *rhs): lhs(lhs), rhs(rhs) {}

    int eval() const {
        return Op<int>()(lhs->eval(), rhs->eval());
    }
};


int eval(const Expression *expr) {
    return expr->eval();
}

template <typename T>
Expression *expr(const T& value) {
    return new Value(value);
}

Expression *expr(Expression *expr) {
    return expr;
}

template <typename U, typename V>
Expression *add(U u, V v) {
    return new BinOp<std::plus>(expr(u), expr(v));
}

template <typename U, typename V>
Expression *sub(U u, V v) {
    return new BinOp<std::minus>(expr(u), expr(v));
}

template <typename U, typename V>
Expression *mul(U u, V v) {
    return new BinOp<std::multiplies>(expr(u), expr(v));
}

template <typename U, typename V>
Expression *div(U u, V v) {
    return new BinOp<std::divides>(expr(u), expr(v));
}

int main() {
    using namespace std;

    cout << eval(add(1, 2)) << endl;
    cout << eval(mul(3, 5)) << endl;
    cout << eval(mul(add(3, 5), sub(7, 2))) << endl;
    cout << eval(div(12, add(3, 1))) << endl;

    return 0;
}
