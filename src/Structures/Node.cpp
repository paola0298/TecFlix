#include "Node.h"

Node::Node(int val) : value(val) { }

int Node::getValue() {
    return value;
}

void Node::setValue(int value) {
    this->value = value;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node* next) {
    this->next = next;
}