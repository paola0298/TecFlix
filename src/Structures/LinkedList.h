#ifndef LINKEDLIST
#define LINKEDLIST

#include "Node.cpp"
#include <iostream>
using namespace std;

template<typename T>

class LinkedList {
    private:
        Node<T> *head;
        int size;

    public:
        Node<T> *tail;
        LinkedList();
        int getSize();
        void insertStart(T value);
        void insertEnd(T value);
        T deleteStart();
        void modify(T value, int index);
        T getValueAtPos(int index);
        void print();
        string getList();
};

#endif