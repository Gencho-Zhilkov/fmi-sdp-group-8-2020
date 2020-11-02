#include <deque>
#include <iostream>
#include <stack>


/*
Имплементирайте функцията sortStack, която приема един стек и го сортира в нарастващ ред (т.е. top <= (top - 1) <= (top - 2), ...).

За целта sortStack може да използва още един помощен стек, но не и други структури от данни.

Каква е сложността на съответния алгоритъм (най-добра, най-лоша, средна)?
*/
template <typename T>
void sortStack(std::stack<T>& st) {
    std::stack<T> temp;

    while(!st.empty()) {
        const T top = st.top();
        st.pop();

        while (!temp.empty() && top < temp.top()) {
            st.push(temp.top());
            temp.pop();
        }

        temp.push(top);
    }

    while(!temp.empty()) {
        st.push(temp.top());
        temp.pop();
    }
}


int main() {
    using namespace std;

    stack<int> st(deque<int> {2, 3, 7, 6, 5, 8});
    sortStack(st);

    while(!st.empty()) {
        cout << st.top() << ' ';
        st.pop();
    }
    cout << endl;

    return 0;
}
