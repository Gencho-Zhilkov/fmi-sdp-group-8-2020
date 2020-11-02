#include <iostream>
#include <stack>
#include <string>

/*
Каква е сложността на алгоритъма: по време? по място?
*/
std::string reverse(std::string str) {
    std::stack<char> reverse;
    for(auto c: str) {
        reverse.push(c);
    }
    std::string res;
    while(!reverse.empty()) {
        res += reverse.top();
        reverse.pop();
    }
    return res;
}


int main() {
    using namespace std;

    cout << reverse("") << endl;
    cout << reverse("bala") << endl;
    cout << reverse("ala bala") << endl;
    cout << reverse("ala") << endl;
    cout << reverse("ala?????") << endl;
    return 0;
}

