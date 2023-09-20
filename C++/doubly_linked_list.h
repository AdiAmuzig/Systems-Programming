//
// Created by adi.amuzig on 13/01/2021.
//

#ifndef HW3_DOUBLY_LINKED_LIST_H
#define HW3_DOUBLY_LINKED_LIST_H

#include <iostream>

using std::ostream;

namespace mtm {
    template<class T>
    class DoublyLinkedList {

    private:
        struct Node {
            T *data;
            Node *next;
            Node *prev;
        public:
            explicit Node(const T &given_data);

            ~Node();
        };

        Node *head;
        Node *end;
        int size;

    public:
        struct Iterator {
            Node *current;

            explicit Iterator(Node *node = nullptr);

            ~Iterator();

            Iterator(const Iterator &old_iterator);

            bool operator==(const Iterator &I2) const;

            bool isLast() const;

            Iterator &operator=(const Iterator &b);

            Iterator &operator++();

            Iterator &operator++() const;

            Iterator &operator--();

            T &operator*();
        };

        DoublyLinkedList();

        ~DoublyLinkedList();

        DoublyLinkedList(const DoublyLinkedList &list);

        DoublyLinkedList &operator=(const DoublyLinkedList &list);

        Iterator insert(const T &value);

        Iterator erase(const T &value);

        Iterator returnHead() const;

        int getSize() const;

        bool dataExists(const T &value) const;

    private:
        Iterator addFirstNode(const T &value);

        void eraseMiddleNode(Node *current_node);

        void insertMiddleNode(Node *current_node, Node *new_node);
    };

    template<class T>
    DoublyLinkedList<T>::Node::Node(const T &given_data) :
            next(nullptr),
            prev(nullptr) {
        data = given_data.clone();
    }

    template<class T>
    DoublyLinkedList<T>::Node::~Node() {
        delete data;
    }

    template<class T>
    DoublyLinkedList<T>::DoublyLinkedList() :
            head(nullptr),
            end(nullptr),
            size(0) {
    }

    template<class T>
    DoublyLinkedList<T>::~DoublyLinkedList() {
        Iterator i(head);
        while (head != nullptr) {
            i = erase(*i);
        }
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator
    DoublyLinkedList<T>::insert(const T &value) {
        if (head == nullptr) {
            return addFirstNode(value);
        }
        Node *new_node = new Node(value);
        Iterator pos = returnHead();
        while (pos.current != end && *pos < value) {
            ++pos;
        }
        Node *current_node = pos.current;
        if (current_node == head && (value < *pos || value == *pos)) {
            new_node->next = current_node;
            current_node->prev = new_node;
            head = new_node;
        } else if (current_node == end && (*pos < value || *pos == value)) {
            new_node->prev = current_node;
            current_node->next = new_node;
            end = new_node;
        } else {
            insertMiddleNode(current_node, new_node);
        }
        size++;
        return ++pos;
    }

    template<class T>
    void DoublyLinkedList<T>::insertMiddleNode(Node *current_node,
                                               Node *new_node) {
        Node *prev_node = current_node->prev;
        prev_node->next = new_node;
        new_node->prev = prev_node;
        current_node->prev = new_node;
        new_node->next = current_node;
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator
    DoublyLinkedList<T>::addFirstNode(const T &value) {
        Node *new_node = new Node(value);
        head = new_node;
        end = new_node;
        Iterator new_pos(head);
        size++;
        return new_pos;
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator
    DoublyLinkedList<T>::erase(const T &value) {
        Iterator pos = returnHead();
        while (pos.current != end && !(*pos == value)) {
            ++pos;
        }
        if (size == 0 || !(*pos == value)) {
            return pos;
        }
        Node *current_node = pos.current;
        if (current_node == head && current_node == end) {
            pos.current = nullptr;
            head = nullptr;
            end = nullptr;
        } else if (current_node == head) {
            ++pos;
            head = current_node->next;
            head->prev = nullptr;
        } else if (current_node == end) {
            --pos;
            end = current_node->prev;
            end->next = nullptr;
        } else {
            ++pos;
            eraseMiddleNode(current_node);
        }
        delete current_node;
        size--;
        return pos;
    }

    template<class T>
    void DoublyLinkedList<T>::eraseMiddleNode(Node *current_node) {
        Node *next_node = current_node->next;
        Node *prev_node = current_node->prev;
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator
    DoublyLinkedList<T>::returnHead() const {
        Iterator i(head);
        return i;
    }

    template<class T>
    int DoublyLinkedList<T>::getSize() const {
        return size;
    }

    template<class T>
    bool DoublyLinkedList<T>::dataExists(const T &value) const {
        Iterator pos = returnHead();
        while (pos.current != end && !(*pos == value)) {
            ++pos;
        }
        if (size == 0 || !(*pos == value)) {
            return false;
        }
        return true;
    }

    template<class T>
    DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &list) {
        int i = list.getSize();
        size = 0;
        DoublyLinkedList<T>::Iterator iterator = list.returnHead();
        for (int j = 0; j < i; ++j) {
            insert(*iterator);
            ++iterator;
        }
    }

    template<class T>
    DoublyLinkedList<T> &
    DoublyLinkedList<T>::operator=(const DoublyLinkedList &list) {
        if (this == &list) {
            return *this;
        }

        while (size != 0) {
            erase(*(returnHead()));
        }

        int new_size = list.getSize();
        DoublyLinkedList<T>::Iterator iterator = list.returnHead();
        for (int j = 0; j < new_size; ++j) {
            insert(*iterator);
            ++iterator;
        }
        return *this;
    }


    template<class T>
    bool DoublyLinkedList<T>::Iterator::operator==(
            const DoublyLinkedList::Iterator &I2) const {
        return current == I2.current;
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator &
    DoublyLinkedList<T>::Iterator::operator++() {
        if (current->next != nullptr) {
            current = current->next;
        }
        return *this;
    }


    template<class T>
    typename DoublyLinkedList<T>::Iterator &
    DoublyLinkedList<T>::Iterator::operator++() const {
        if (current->next != nullptr) {
            current = current->next;
        }
        return *this;
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator &
    DoublyLinkedList<T>::Iterator::operator--() {
        if (current->prev != nullptr) {
            current = current->prev;
        }
        return *this;
    }

    template<class T>
    T &DoublyLinkedList<T>::Iterator::operator*() {
        return *(current->data);
    }

    template<class T>
    DoublyLinkedList<T>::Iterator::Iterator(DoublyLinkedList::Node *node) {
        current = node;
    }

    template<class T>
    typename DoublyLinkedList<T>::Iterator &
    DoublyLinkedList<T>::Iterator::operator=(
            const DoublyLinkedList::Iterator &b) {
        current = b.current;
        return *this;
    }

    template<class T>
    DoublyLinkedList<T>::Iterator::~Iterator() {
        current = nullptr;
    }

    template<class T>
    DoublyLinkedList<T>::Iterator::Iterator(
            const DoublyLinkedList::Iterator &old_iterator) :
            current(old_iterator.current) {
    }

    template<class T>
    bool DoublyLinkedList<T>::Iterator::isLast() const {
        return (current->next == nullptr);
    }

}

#endif //HW3_DOUBLY_LINKED_LIST_H
