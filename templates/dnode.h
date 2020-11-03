#ifndef _SDP_FMI_DNODE_H_
#define _SDP_FMI_DNODE_H_


template<typename T>
class DListIterator;

template<typename T>
class DList;

template<typename T>
class DTailQ;


template <typename T>
class DNode {
private:
    friend class DListIterator<T>;
    friend class DList<T>;
    friend class DTailQ<T>;

    T value;
    DNode *prev;
    DNode *next;

    DNode(const T& value, DNode *prev = nullptr, DNode *next = nullptr):
        value(value), prev(prev), next(next) {}
};


template <typename T>
class DListIterator {
private:
    friend class DList<T>;
    friend class DTailQ<T>;

    DNode<T> *node;

public:
    DListIterator(DNode<T>* node): node(node) {}

    T& operator*() {
        return node->value;
    }

    DListIterator& operator++() {
        node = node->next;
        return *this;
    }

    DListIterator& operator--() {
        node = node->prev;
        return *this;
    }

    bool operator==(const DListIterator& that) const {
        return node == that.node;
    }

    bool operator!=(const DListIterator& that) const {
        return node != that.node;
    }
};


#endif /* _SDP_FMI_DNODE_H_ */
