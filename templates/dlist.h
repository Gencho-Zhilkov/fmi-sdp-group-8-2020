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
        headPtr = new DNode<T>(value, nullptr, headPtr);
        if (headPtr->next) {
            headPtr->next->prev = headPtr;
        }
    }

    void insertBefore(iterator it, const T& value) {
        if(it == begin()) {
            insertHead(value);
        } else if(it == end()) {
            // end is invalid, so we cannot insert before it.
            throw std::domain_error("Insert before end of list!");
        } else {
            auto node = it.node, prev = node->prev;
            node->prev = new DNode(value, prev, node);
            prev->next = node->prev;
        }
    }

    void insertAfter(iterator it, const T& value) {
        if(it == end()) {
            throw std::domain_error("Insert after end of list!");
        }
        auto node = it.node, next = node->next;
        node->next = new DNode(value, node, next);
        if (next != nullptr) {
            next->prev = node->next;
        }
    }

    void removeHead() {
        if (empty()) {
            throw std::domain_error("Remove from empty list!");
        }
        auto temp = headPtr;
        headPtr = headPtr->next;
        if (headPtr != nullptr) {
            headPtr->prev = nullptr;
        }
        delete temp;
    }

    void removeBefore(iterator it) {
        if (it == begin()) {
            throw std::domain_error("Remove before start of list!");
        }
        auto node = it.node, prev = node->prev;
        node->prev = prev->prev;
        if (node->prev != nullptr) {
            node->prev->next = node;
        } else {
            headPtr = node;
        }
        delete prev;
    }

    void removeAfter(iterator it) {
        auto node = it.node, next = node->next;
        if (next == nullptr) {
            throw std::domain_error("Remove after last list element!");
        }
        node->next = next->next;
        if (next->next) {
            next->next->prev = node;
        }
        delete next;
    }

    void removeAt(iterator it) {
        if (it == end()) {
            throw std::domain_error("Remove at end of list!");
        }
        auto node = it.node, prev = node->prev, next = node->next;
        delete node;
        if (prev != nullptr) {
            prev->next = next;
        } else {
            headPtr = next;
        }

        if (next != nullptr) {
            next->prev = prev;
        }
        // Question: what do we do with it.node?
        it.node = next;
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
