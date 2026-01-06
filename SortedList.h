#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    public:
    private:
        class Node {
        private:
            T data;
            Node* next;
        public:
            Node()=default;
            Node(const T& data) : data(data), next(nullptr) {}
        };

        Node* head;
        int size;

    public:
        template<typename Predicate>
        SortedList<T> filter(Predicate p) {
            SortedList<T> result(*this);
            for (ConstIterator it = begin(); it != end(); it++){
                if (p(*it)) {
                    result.insert(*it);
                }
            }
            return result;
        }

        template<typename Operation>
        SortedList<T> apply(Operation operation) const {
            SortedList<T> result;
            for (ConstIterator it = begin(); it != end(); it++) {
                result.insert(operation(it));
            }
            return result;
        }

        ConstIterator begin() const {
            return ConstIterator(head);
        }

        ConstIterator end() const {
            return ConstIterator(nullptr);
        }
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

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