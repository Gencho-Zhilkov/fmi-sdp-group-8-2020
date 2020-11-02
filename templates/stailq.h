#ifndef _SDP_FMI_STAILQ_H_
#define _SDP_FMI_STAILQ_H_

#include <cassert>
#include <initializer_list>
#include <stdexcept>

#include "snode.h"


template <typename T>
class STailQ {
public:
    typedef SListIterator<T> iterator;

private:
    SNode<T> *headPtr;
    SNode<T> *tailPtr;

    void copy(iterator begin, iterator end) {
        for(auto it = begin; it != end; ++it) {
            insertTail(*it);
        }
    }

    void erase() {
        while(!empty()) {
            removeHead();
        }
    }

public:
    STailQ(): headPtr(nullptr), tailPtr(nullptr) {}

    STailQ(std::initializer_list<T> l) : STailQ() {
        for(auto it = l.begin(); it != l.end(); ++it) {
            insertTail(*it);
        }
    }

    STailQ(const STailQ& that) : STailQ() {
        copy(that.begin(), that.end());
    }

    STailQ& operator=(const STailQ& that) {
        if(this != &that) {
            erase();
            copy(that.begin(), that.end());
        }
        return *this;
    }

    ~STailQ() {
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

    T& tail() {
        if (empty()) {
            throw std::domain_error("Tail of empty list!");
        }
        return tailPtr->value;
    }

    // Mutations
    void insertHead(const T& value) {
        headPtr = new SNode(value, headPtr);
        if (tailPtr == nullptr) {
            tailPtr = headPtr;
        }
    }

    void removeHead() {
        if (empty()) {
            throw std::domain_error("Remove from head of empty list!");
        }
        SNode<T> *tmp = headPtr;
        if(tailPtr == tmp) {
            tailPtr = tmp->next;
        }
        headPtr = tmp->next;
        delete tmp;
    }

    void insertAfter(iterator it, const T& value) {
        if(it == end()) {
            throw std::domain_error("Insert after end of list!");
        }
        it.node->next = new SNode(value, it.node->next);
        if(it.node == tailPtr) {
            tailPtr = it.node->next;
        }
    }

    void removeAfter(iterator it) {
        if(it.node->next == nullptr) {
            throw std::domain_error("Remove after last list element!");
        }
        SNode<T> *tmp = it.node->next;
        if(tailPtr == tmp) {
            tailPtr = tmp->next;
        }
        it.node = tmp->next;
        delete tmp;
    }

    void insertTail(const T& value) {
        if (empty()) {
            headPtr = tailPtr = new SNode(value);
        } else {
            tailPtr->next = new SNode(value);
            tailPtr = tailPtr->next;
        }
    }

    // O(n) time - can we have this as O(1) ?
    void removeTail() {
        if (empty()) {
            throw std::domain_error("Remove from tail of empty list!");
        }
        auto it = begin();
        while(it.node->next != tailPtr) {
            ++it;
        }
        removeAfter(it);
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

    // TODO: Equality operators
    // TODO: lexicographical ordering
};

#endif /* _SDP_FMI_STAILQ_H_ */
