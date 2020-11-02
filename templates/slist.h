#ifndef _SDP_FMI_SLIST_H_
#define _SDP_FMI_SLIST_H_

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

#include "snode.h"


template <typename T>
class SList {
public:
    typedef SListIterator<T> iterator;

private:
    SNode<T> *headPtr;

    static SNode<T> *copy(iterator begin, iterator end) {
        return begin == end ? nullptr : new SNode(*begin, copy(++begin, end));
    }

    void erase() {
        while(!empty()) {
            removeHead();
        }
    }

    void remove(SNode<T>*& node) {
        SNode<T> *toDelete = node;
        node = toDelete->next;
        delete toDelete;
    }

public:
    SList(): headPtr(nullptr) {}

    SList(std::initializer_list<T> l) : SList() {
        for(auto it = std::rbegin(l); it != std::rend(l); ++it) {
            insertHead(*it);
        }
    }

    SList(const SList& that) {
        headPtr = copy(that.begin(), that.end());
    }

    SList& operator=(const SList& that) {
        if(this != &that) {
            erase();
            headPtr = copy(that.begin(), that.end());
        }
        return *this;
    }

    ~SList() {
        erase();
    }

    bool empty() const {
        return headPtr == nullptr;
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
        headPtr = new SNode(value, headPtr);
    }

    void removeHead() {
        if (empty()) {
            throw std::domain_error("Remove from empty list!");
        }
        remove(headPtr);
    }

    void insertAfter(iterator it, const T& value) {
        if(it == end()) {
            throw std::domain_error("Insert after end of list!");
        }
        it.node->next = new SNode(value, it.node->next);
    }

    void removeAfter(iterator it) {
        if(it.node->next == nullptr) {
            throw std::domain_error("Remove after last list element!");
        }
        remove(it.node->next);
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
    bool operator==(const SList& that) const {
        if (this == &that) {
            return true;
        }
        auto i1 = begin(), i2 = that.begin();
        for(; i1 != end() && i2 != that.end(); ++i1, ++i2) {
            if (*i1 != *i2) {
                return false;
            }
        }
        return (i1 == end()) && (i2 == that.end());
    }

    bool operator!=(const SList& that) const {
        return !(*this == that);
    }

    // TODO: lexicographical ordering
};

#endif /* _SDP_FMI_SLIST_H_ */
