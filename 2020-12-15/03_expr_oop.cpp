#include <iostream>

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

class BinOp: public Expression {
protected:
    Expression *lhs;
    Expression *rhs;

public:
    BinOp(const int lval, const int rval) {
        lhs = new Value(lval);
        rhs = new Value(rval);
    }

    BinOp(const int lval, Expression *rhs): rhs(rhs) {
        lhs = new Value(lval);
    }

    BinOp(const int lval, Expression *rhs): rhs(rhs) {
        lhs = new Value(lval);
    }

    BinOp(Expression *lhs, Expression *rhs): lhs(lhs), rhs(rhs) {}
};

class Add: public BinOp {
public:
    using BinOp::BinOp;

    virtual int eval() const {
        return this->lhs->eval() + this->rhs->eval();
    }
};

class Sub: public BinOp {
public:
    using BinOp::BinOp;

    virtual int eval() const {
        return this->lhs->eval() - this->rhs->eval();
    }
};

class Mul: public BinOp {
public:
    using BinOp::BinOp;

    virtual int eval() const {
        return this->lhs->eval() * this->rhs->eval();
    }
};

class Div: public BinOp {
public:
    using BinOp::BinOp;

    virtual int eval() const {
        return this->lhs->eval() / this->rhs->eval();
    }
};

int eval(const Expression *expr) {
    return expr->eval();
}


int main() {
    using namespace std;

    cout << eval(new Add(1, 2)) << endl;
    cout << eval(new Mul(3, 5)) << endl;
    cout << eval(new Mul(new Add(3, 5), new Sub(7, 2))) << endl;
    cout << eval(new Div(12, new Add(3, 1))) << endl;

    return 0;
}
