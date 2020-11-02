#include <iostream>
#include <stack>
#include <stdexcept>


/*
Използвайте два стека, за да имплементирате опашка,
която има следните методи:
 - bool empty()
 - void enqueue(const T& value)
 - T dequeue()

Каква е сложността на всеки от методите и защо?
*/
template <typename T>
class StackedQueue {
private:
    std::stack<T> push, pop;

public:
    bool empty() const {
        return push.empty() && pop.empty();
    }

    void enqueue(const T& value) {
        push.push(value);
    }

    T dequeue() {
        if (empty()) {
            throw std::runtime_error("Empty queue!");
        }

        if (pop.empty()) {
            while(!push.empty()) {
                pop.push(push.top());
                push.pop();
            }
        }

        auto res = pop.top();
        pop.pop();
        return res;
    }
};


int main() {
    using namespace std;

    StackedQueue<int> q;
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    q.enqueue(7);

    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;

    q.enqueue(2);
    q.enqueue(4);

    cout << q.dequeue() << endl;

    q.enqueue(6);
    q.enqueue(8);

    while(!q.empty()) {
        cout << q.dequeue() << endl;
    }

    return 0;
}
