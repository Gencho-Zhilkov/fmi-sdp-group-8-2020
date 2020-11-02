#include <iostream>
#include <stack>
#include <string>


bool validBrackets(std::string line) {
    std::stack<char> openBrackets;

    for(auto c: line) {
        std::cout << c;
        switch(c) {
        case '(':
            openBrackets.push(')');
            break;
        case '[':
            openBrackets.push(']');
            break;
        case '{':
            openBrackets.push('}');
            break;
        case ')': case ']': case '}':
            if(openBrackets.empty() || openBrackets.top() != c) {
                return false;
            } else {
                openBrackets.pop();
            }
            break;
        default:
            break;
        }
    }
    return openBrackets.empty();
}


int main() {
    using namespace std;

    cout << validBrackets("()") << endl;
    cout << validBrackets("(") << endl;
    cout << validBrackets("}") << endl;
    cout << validBrackets("{[()]}") << endl;
    cout << validBrackets("<{[()]}>") << endl;
    cout << validBrackets("(<{[()]}>)") << endl;
    cout << validBrackets("asd(asda<dd>ddd(asd{123[sa(a<a)d]ba}as)<d>asd)a") << endl;
    return 0;
}
