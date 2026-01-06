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

     void copyNodes(const SortedList<T>& other) {
            if (!other.head) return;
            Node* last = nullptr;
            Node* currOther = other.head;
            while (currOther) {
                Node* newNode = new Node(currOther->data);
                if (!head) head = newNode;
                else last->next = newNode;
                last = newNode;
                currOther = currOther->next;
            }
            size = other.size;
        }

        void destroyList() {
            while (head) {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            size = 0;
        }

    public:
   class ConstIterator;
        SortedList() : head(nullptr), size(0) {}
        SortedList(const SortedList<T>& other) : head(nullptr), size(0) { copyNodes(other); }
        SortedList& operator=(const SortedList<T>& other) {
            if (this != &other) {
                destroyList();
                copyNodes(other);
            }
            return *this;
        }
        ~SortedList() { destroyList(); }
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
                if (!current) throw std::out_of_range("Iterator out of range");
                current = current->next;
                return *this;
            }

            const T& operator*() const {
                if (!current) throw std::out_of_range("Iterator out of range");
                return current->data;
            }

            bool operator!=(const ConstIterator& other) const {
                if (list != other.list) throw std::runtime_error("Comparing iterators from different lists");
                return current != other.current;
            }
        };
  void insert(const T& value) {
            Node* newNode = new Node(value);
            if (!head || value > head->data) { // Descending order
                newNode->next = head;
                head = newNode;
            } else {
                Node* curr = head;
                while (curr->next && curr->next->data > value) {
                    curr = curr->next;
                }
                newNode->next = curr->next;
                curr->next = newNode;
            }
            size++;
        }

        void remove(const ConstIterator& iter) {
            if (!iter.current) return;
            if (iter.current == head) {
                Node* temp = head;
                head = head->next;
                delete temp;
                size--;
                return;
            }
            Node* curr = head;
            while (curr->next && curr->next != iter.current) {
                curr = curr->next;
            }
            if (curr->next) {
                Node* temp = curr->next;
                curr->next = temp->next;
                delete temp;
                size--;
            }
        }

        int length() const {
            return size;
        }


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
