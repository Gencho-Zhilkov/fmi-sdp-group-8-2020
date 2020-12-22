#include <iostream>
#include <deque>

template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;

    Node(const T& value, Node<T> *left = nullptr, Node<T> *right = nullptr):
        value(value), left(left), right(right) {}
};


// Дефинирайте функцята sumProd(tree), която приема
// двоично дърво от цели числа tree и връща сумата от
// сбора на стойностите на върховете, намиращи се на
// четно ниво и произведението на стойностите на
// върховете на нечетно ниво.

// Итеративно решение с обхождане в ширина.
int sumProd(const Node<int>* root) {
    int sum = 0, prod = 1;
    int level = 0;

    std::deque<const Node<int>*> currNodes;
    if(root != nullptr) {
        currNodes.push_back(root);
    }

    while (!currNodes.empty()) {
        std::deque<const Node<int>*> nextNodes;

        for(auto node: currNodes) {
            if (level % 2 == 0) {
                sum += node->value;
            } else {
                prod *= node->value;
            }

            if(node->left != nullptr) {
                nextNodes.push_back(node->left);
            }
            if(node->right != nullptr) {
                nextNodes.push_back(node->right);
            }
        }

        currNodes = nextNodes;
        level ++;
    }

    return sum + prod;
}


// Рекурсивно решение, с обхождане в дълбочина
void doSumProd(const Node<int>* node, const int level, int *sum, int *prod) {
    if (node != nullptr) {
        if (level % 2 == 0) {
            *sum += node->value;
        } else {
            *prod *= node->value;
        }

        doSumProd(node->left, level+1, sum, prod);
        doSumProd(node->right, level+1, sum, prod);
    }
}

int sumProd_rec(const Node<int>* node) {
    int sum = 0, prod = 1;
    doSumProd(node, 0, &sum, &prod);
    return sum + prod;
}


int main() {
    using namespace std;

    //       1
    //    /     \
    //   2       3
    //  / \     / \
    // 4   5   6   7
    auto tree1 = new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    );

    //       4
    //    /     \
    //   2       6
    //  / \     / \
    // 1   3   5   7
    auto tree2 = new Node(4,
        new Node(2, new Node(1), new Node(3)),
        new Node(6, new Node(5), new Node(7))
    );

    cout << sumProd(nullptr) << endl;
    cout << sumProd(tree1) << endl;
    cout << sumProd(tree2) << endl;

    cout << sumProd_rec(nullptr) << endl;
    cout << sumProd_rec(tree1) << endl;
    cout << sumProd_rec(tree2) << endl;

    return 0;
}
