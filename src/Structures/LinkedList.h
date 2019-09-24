#ifndef LINKEDLIST
#define LINKEDLIST

#include "Node.cpp"
#include <iostream>
using namespace std;

class LinkedList {
    private:
        Node *head;
        int size;

    public:
        Node *tail;
        LinkedList();
        int getSize();
        void insertStart(int value);
        void insertEnd(int value);
        int deleteStart();
        void modify(int value, int index);
        int getValueAtPos(int index);
        void print();
        string getList();
};

#endif