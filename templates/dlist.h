#ifndef _SDP_FMI_DLIST_H_
#define _SDP_FMI_DLIST_H_

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

#include "dnode.h"


template <typename T>
class DList {
public:
    typedef DListIterator<T> iterator;

private:
    DNode<T> *headPtr;

    static DNode<T> *copy(iterator begin, iterator end) {
        if (begin == end) {
            return nullptr;
        }

        auto thiz = new DNode(*begin);
        auto next = copy(++begin, end);
        thiz->next = next;
        if (next != nullptr) {
            next->prev = thiz;
        }
        return thiz;
    }

    void erase() {
        while(!empty()) {
            removeHead();
        }
    }

public:
    DList(): headPtr(nullptr) {}

    DList(std::initializer_list<T> l) : DList() {
        for(auto it = std::rbegin(l); it != std::rend(l); ++it) {
            insertHead(*it);
        }
    }

    DList(const DList& that) {
        headPtr = copy(that.begin(), that.end());
    }

    DList& operator=(const DList& that) {
        if(this != &that) {
            erase();
            headPtr = copy(that.begin(), that.end());
        }
        return *this;
    }

    ~DList() {
        erase();
    }

    bool empty() const {
        return begin() == end();
    }

    size_t size() const {
        size_t res = 0;
        for(auto it = begin(); it != end(); ++it) {
            ++res;
        }
        return res;
    }

    T& head() {
        if (empty()) {
            throw std::domain_error("Head of empty list!");
        }
        return headPtr->value;
    }

    // Mutations
    void insertHead(const T& value) {
    }

    void insertBefore(iterator it, const T& value) {
        // TODO
    }

    void insertAfter(iterator it, const T& value) {
        // TODO
    }

    void removeHead() {
        // TODO
    }

    void removeBefore(iterator it) {
        // TODO
    }

    void removeAfter(iterator it) {
        // TODO
    }

    void removeAt(iterator it) {
        // TODO
        // Question: what do we do with it.node?
    }

    // Iterators
    iterator begin() {
        return iterator(headPtr);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const iterator begin() const {
        return iterator(headPtr);
    }

    const iterator end() const {
        return iterator(nullptr);
    }

    // Equality operators
    bool operator==(const DList& that) const {
        if (this == &that) {
            return true;
        }
        return std::equal(begin(), end(), that.begin(), that.end());
    }

    bool operator!=(const DList& that) const {
        return !(*this == that);
    }

    // TODO: lexicographical ordering
};

#endif /* _SDP_FMI_DLIST_H_ */
