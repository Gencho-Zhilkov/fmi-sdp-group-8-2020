#ifndef _SDP_FMI_SNODE_H_
#define _SDP_FMI_SNODE_H_


template<typename T>
class SListIterator;

template<typename T>
class SList;

template<typename T>
class STailQ;


template <typename T>
class SNode {
private:
    friend class SListIterator<T>;
    friend class SList<T>;
    friend class STailQ<T>;

    T value;
    SNode *next;

    SNode(const T& value, SNode *next = nullptr):
        value(value), next(next) {}
};


template <typename T>
class SListIterator {
private:
    friend class SList<T>;
    friend class STailQ<T>;

    SNode<T> *node;

public:
    SListIterator(SNode<T>* node): node(node) {}

    T& operator*() {
        return node->value;
    }

    SListIterator& operator++() {
        node = node->next;
        return *this;
    }

    bool operator==(const SListIterator& that) const {
        return node == that.node;
    }

    bool operator!=(const SListIterator& that) const {
        return node != that.node;
    }
};


#endif /* _SDP_FMI_SNODE_H_ */
