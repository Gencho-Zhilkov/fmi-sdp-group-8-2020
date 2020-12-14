#include <iostream>
#include <string>
#include <list>
#include <map>

#include "../templates/tree.h"


// Зад 1. Проверка дали едно двойчно дърво е наредено
template<typename T>
bool isBST(Tree<T>& tree) {
    T previous;
    auto inOrder = tree.inOrder();
    for(auto it = inOrder.begin(); it != inOrder.end(); ++it) {
        if (it == inOrder.begin()) {
            previous = *it;
            continue;
        }

        if (previous >= *it) {
            return false;
        }

        previous = *it;
    }
    return true;
}


// Зад 2. Да се намери най-близкия общ прародител на два върха в
// наредено двойчно дърво. За целта може да допуснете, че дървото
// със сигурност съдържа елементи със стойности x и y.
template<typename T>
T mostRecentCommonAncestor(Node<T> *node, const T& x, const T& y) {
    if(node->value < x && node->value < y) {
        return mostRecentCommonAncestor(node->right, x, y);
    }
    else if(node->value > x && node->value > y) {
        return mostRecentCommonAncestor(node->left, x, y);
    } else {
        return node->value;
    }
}


// Зад 3. Ransom note: проверка дали всички думи в списъка note се съдържат
// в списъка newspaper.
bool canWrite(std::list<std::string> newspaper, std::list<std::string> note) {
    // std::hash_map<std::string, int> wordsCount;
    std::map<std::string, int> wordsCount;

    for(auto word: newspaper) {
        wordsCount[word] ++;
    }
    for(auto word: note) {
        auto count = wordsCount[word];
        if (count == 0) {
            return false;
        }
        wordsCount[word] --;
    }
    return true;
}


int main() {
    using namespace std;

    //       1
    //    /     \
    //   2       3
    //  / \     / \
    // 4   5   6   7
    Tree<int> tree1(new Node(1,
        new Node(2, new Node(4), new Node(5)),
        new Node(3, new Node(6), new Node(7))
    ));
    //       4
    //    /     \
    //   2       6
    //  / \     / \
    // 1   3   5   7
    auto node = new Node(40,
        new Node(20, new Node(10), new Node(30)),
        new Node(60, new Node(50), new Node(70))
    );
    Tree<int> tree2(node);

    // Зад 1.
    cout << isBST(tree1) << endl;
    cout << isBST(tree2) << endl;

    // Зад 2.
    cout << mostRecentCommonAncestor(node, 50, 70) << endl;
    cout << mostRecentCommonAncestor(node, 10, 30) << endl;
    cout << mostRecentCommonAncestor(node, 80, 56) << endl;

    // Зад 3.
    cout << canWrite({"One", "One", "Two", "Three"}, {"One"}) << endl;
    cout << canWrite({"One", "One", "Two", "Three"}, {"One", "One"}) << endl;
    cout << canWrite({"One", "One", "Two", "Three"}, {"One", "Two"}) << endl;
    cout << canWrite({"One", "One", "Two", "Three"}, {"Two", "Two"}) << endl;
    cout << canWrite({"One", "One", "Two", "Three"}, {"Four"}) << endl;

    return 0;
}
