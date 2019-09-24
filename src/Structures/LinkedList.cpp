#include "LinkedList.h"

LinkedList::LinkedList(){
    size = 0;
    head = nullptr;
    tail = nullptr;
}

int LinkedList::getSize(){
    return size;
}

void LinkedList::insertStart(int value) {
    Node *temp = new Node(value);
    if (size > 0) {
        temp->setNext(head);
    }
    if (size == 1)
        tail = head;
    head = temp;
    size++;
}

void LinkedList::insertEnd(int value) {
    Node *newNode = new Node(value);
    tail->setNext(newNode);
    tail = newNode;
    size++;
}

int LinkedList::deleteStart(){

    if (size>0){
        int value = head->getValue();
        Node *temp = head->getNext();
        delete(head);
        if (size == 1) {
            tail = temp;
        }
        head = temp;
        size--;
        return value;
    }
    

    return -1;
}

void LinkedList::modify(int value, int index){
    if (index >= 0 && index < size){
        Node *temp = head;
        int count = 0;
        while (count<index) {
            temp = temp->getNext();
            count++;
        }
        temp->setValue(value);
    }
}

int LinkedList::getValueAtPos(int index){
    if (index >= 0 && index < size) {
        Node *temp = head;
        int count = 0;
        while (count<index) {
            temp = temp->getNext();
            count++;
        }
        return temp->getValue();
    } else {
        return -1;
    }
}

void LinkedList::print(){
    Node *temp = head;
    cout << "[";
    for (int i=0; i<size; i++) {
        if (i == size-1){
            cout << temp->getValue();
        } else {
            cout << temp->getValue() << ", ";
        }
        temp = temp->getNext();
    }

    cout << "]\n";
}

string LinkedList::getList(){
    Node *temp = head;
    string list;
    list.append("[");
    // cout << "[";
    for (int i=0; i<size; i++) {
        if (i == size-1){
            // cout << temp->getValue();
            list.append(to_string(temp->getValue()));
        } else {
            // cout << temp->getValue() << ", ";
            list.append(to_string(temp->getValue()));
            list.append(", ");
        }
        temp = temp->getNext();
    }

    // cout << "]\n";
    list.append("]");

    cout << list.data() << "\n";
    return list.data();
}

// int main(int argc, char *argv[]) { 
//     LinkedList *list = new LinkedList();
    
//     list->print();

//     list->insertStart(5);
//     list->insertStart(9);
//     list->insertStart(23);
//     list->insertStart(7);
//     list->insertStart(1);
//     cout << "tail: " << list->tail->getValue() << "\n";
//     list->insertEnd(100);

//     cout << "tail: " << list->tail->getValue() << "\n";

//     list->print();

//     list->deleteStart();
//     list->deleteStart();
//     list->deleteStart();
//     list->deleteStart();
//     cout << "tail: " << list->tail->getValue() << "\n";

//     list->print();

//     list->modify(500, 2);

//     list->print();

//     cout << "tail: " << list->tail->getValue() << "\n";

// }