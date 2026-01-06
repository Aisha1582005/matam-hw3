#pragma once
#include <stdexcept>

namespace mtm {

template <typename T>
class SortedList {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val, Node* nxt = nullptr) : value(val), next(nxt) {}
    };

    Node* head;
    int size;

    void destroyList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    void copyNodes(const SortedList& other) {
        if (!other.head) return;

        head = new Node(other.head->value);
        Node* curr = head;
        Node* otherCurr = other.head->next;

        while (otherCurr) {
            curr->next = new Node(otherCurr->value);
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
    }

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

        bool operator!=(const ConstIterator& it) const {
            if (list != it.list)
                throw std::runtime_error("Comparing iterators from different lists");
            return current != it.current;
        }

        const T& operator*() const {
            if (!current)
                throw std::out_of_range("Iterator out of range");
            return current->value;
        }

        ConstIterator& operator++() {
            if (!current)
                throw std::out_of_range("Iterator out of range");
            current = current->next;
            return *this;
        }
    };

    SortedList() : head(nullptr), size(0) {}

    SortedList(const SortedList& other) : head(nullptr), size(other.size) {
        copyNodes(other);
    }

    SortedList& operator=(const SortedList& other) {
        if (this != &other) {
            SortedList temp(other);
            std::swap(head, temp.head);
            size = other.size;
        }
        return *this;
    }

    ~SortedList() {
        destroyList();
    }

    void insert(const T& value) {
        Node* newNode = new Node(value);
        if (!head || value > head->value) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next && curr->next->value > value) {
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

    ConstIterator begin() const {
        return ConstIterator(this, head);
    }

    ConstIterator end() const {
        return ConstIterator(this, nullptr);
    }

    template <class Predicate>
    SortedList filter(Predicate pred) const {
        SortedList result;
        for (ConstIterator it = begin(); it != end(); ++it) {
            if (pred(*it)) result.insert(*it);
        }
        return result;
    }

    template <class Operation>
    SortedList apply(Operation op) const {
        SortedList result;
        for (ConstIterator it = begin(); it != end(); ++it) {
            result.insert(op(*it));
        }
        return result;
    }

    void unionize(const SortedList& other) {
        for (ConstIterator it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
    }
};

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

