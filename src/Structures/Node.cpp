#include "Node.hpp"

template<typename T>
Node<T>::Node(T val) : value(val) { }

template<typename T>
T Node<T>::getValue() {
    return value;
}

template<typename T>
void Node<T>::setValue(T value) {
    this->value = value;
}

template<typename T>
Node<T>* Node<T>::getNext() {
    return next;
}

template<typename T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}