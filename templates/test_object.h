#ifndef _SDP_FMI_TEST_OBJECT_H_
#define _SDP_FMI_TEST_OBJECT_H_

#include <iostream>

class Test {
    using namespace std;

public:
    Test() {
        cout << "Ctor: this=" << this << endl;
    }

    Test(const Test& that) {
        cout << "Copy: this=" << this << ", that=" << &that << endl;
    }

    Test(Test&& that) {
        cout << "Move: this=" << this << ", that=" << &that << endl;
    }

    Test& operator = (const Test &that) {
        cout << "Assing: this=" << this << ", that=" << &that << endl;
        return *this;
    }

    Test& operator = (const Test &&that) {
        cout << "Move Assing: this=" << this << ", that=" << &that << endl;
        return *this;
    }

    virtual ~Test() {
        cout << "Dtor: this=" << this << endl;
    }
};

#endif /* _SDP_FMI_TEST_OBJECT_H_ */
