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

enum Op {
    VAL,
    ADD,
    SUB,
    MUL,
    DIV,
};

struct Expr {
    Op op;
    union {
        int e_val;
        struct {
            Expr *lhs;
            Expr *rhs;
        } e_op;
    };
};

Expr *val(const int value) {
    return new Expr{ .op = VAL, .e_val = value };
}

Expr *op(const Op op, Expr *lhs, Expr *rhs) {
    return new Expr{ .op = op, .e_op = { lhs, rhs} };
}

int eval(const Expr *expr) {
    switch (expr->op) {
        case VAL:
            return expr->e_val;
        case ADD:
            return eval(expr->e_op.lhs) + eval(expr->e_op.rhs);
        case SUB:
            return eval(expr->e_op.lhs) - eval(expr->e_op.rhs);
        case MUL:
            return eval(expr->e_op.lhs) * eval(expr->e_op.rhs);
        case DIV:
            return eval(expr->e_op.lhs) / eval(expr->e_op.rhs);
        default:
            abort();
    }
}

Expr *add(const int v1, const int v2) {
    return op(ADD, val(v1), val(v2));
}

Expr *add(const int v1, Expr* e2) {
    return op(ADD, val(v1), e2);
}

Expr *add(Expr *e1, const int v2) {
    return op(ADD, e1, val(v2));
}

Expr *add(Expr* e1, Expr* e2) {
    return op(ADD, e1, e2);
}

#define GEN_EXPR(OP, NAME) \
Expr *NAME(const int v1, const int v2) { \
    return op(OP, val(v1), val(v2)); \
} \
 \
Expr *NAME(const int v1, Expr* e2) { \
    return op(OP, val(v1), e2); \
} \
 \
Expr *NAME(Expr *e1, const int v2) { \
    return op(OP, e1, val(v2)); \
} \
 \
Expr *NAME(Expr* e1, Expr* e2) { \
    return op(OP, e1, e2); \
}

// GEN_EXPR(ADD, add)
GEN_EXPR(SUB, sub)
GEN_EXPR(MUL, mul)
GEN_EXPR(DIV, divide)

int main() {
    using namespace std;

    cout << eval(add(1, 2)) << endl;
    cout << eval(mul(3, 5)) << endl;
    cout << eval(mul(add(3, 5), sub(7, 2))) << endl;
    cout << eval(divide(12, add(3, 1))) << endl;

    return 0;
}
