#pragma once
#include <stdexcept>

namespace mtm {

template <typename T>
class SortedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    int size;

    void destroyList();
    void copyNodes(const SortedList& other);
public:
    class ConstIterator {
    private:
        const SortedList* list;
        Node* current;

        ConstIterator(const SortedList* lst, Node* curr) : list(lst), current(curr) {}
        friend class SortedList;

    public:
        ConstIterator() = default;
        ConstIterator(const ConstIterator&) = default;
        ConstIterator& operator=(const ConstIterator&) = default;
        ~ConstIterator() = default;

        ConstIterator& operator++() {
            if (!current) {
                throw std::out_of_range("Iterator out of range");
            }
            current = current->next;
            return *this;
        }

        const T& operator*() const {
            if (!current) {
                throw std::out_of_range("Iterator out of range");
            }
            return current->data;
        }

        bool operator!=(const ConstIterator& other) const {
            if (list != other.list) {
                throw std::runtime_error("Comparing iterators from different lists");
            }
            return current != other.current;
        }
    };
  
     SortedList();
    SortedList(const SortedList& other);
    SortedList& operator=(const SortedList& other);
    ~SortedList();

    ConstIterator begin() const;
    ConstIterator end() const;

    void insert(const T& value);
    void remove(const ConstIterator& iter);
    int length() const;

    template <class Predicate>
    SortedList filter(Predicate pred) const;

    template <class Operation>
    SortedList apply(Operation op) const;
};

    template <class T>
    class SortedList<T>::ConstIterator {
    private:
        const Node* node;
        explicit ConstIterator(const Node* node) : node(node) {}
        friend class SortedList;

    public:
        ~ConstIterator() = default;
        ConstIterator& operator=(const ConstIterator&) = default;
        ConstIterator(const ConstIterator&) = default;

        bool operator!=(const ConstIterator& it) const {
            if (it != *this) {
                return true;
            }
            return false;
        }

        const T& operator*() const {
            if (node == nullptr) {
                throw std::out_of_range("out of range");
            }
            return node->data;
        }
        /**
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~ConstIterator() - destructor
         *
         * operators:
         * 5. operator* - returns the element the iterator points to
         * 6. operator++ - advances the iterator to the next element
         * 7. operator!= - returns true if the iterator points to a different element
         *
         */
    };
}
