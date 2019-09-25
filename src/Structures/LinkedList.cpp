#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList(){
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
int LinkedList<T>::getSize(){
    return size;
}

template<typename T>
void LinkedList<T>::insertStart(T value) {
    Node<T> *temp = new Node<T>(value);
    if (size > 0) {
        temp->setNext(head);
    }
    if (size == 1)
        tail = head;
    head = temp;
    size++;
}

template<typename T>
void LinkedList<T>::insertEnd(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (size > 0) {
        tail->setNext(newNode);
        tail = newNode;
    } else {
        head = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
T LinkedList<T>::deleteStart(){

    if (size>0){
        T value = head->getValue();
        Node<T> *temp = head->getNext();
        delete(head);
        if (size == 1) {
            tail = temp;
        }
        head = temp;
        size--;
        return value;
    }
    return NULL;
}

template<typename T>
void LinkedList<T>::modify(T value, int index){
    if (index >= 0 && index < size){
        Node<T> *temp = head;
        int count = 0;
        while (count<index) {
            temp = temp->getNext();
            count++;
        }
        temp->setValue(value);
    }
}

template<typename T>
T LinkedList<T>::getValueAtPos(int index){
    if (index >= 0 && index < size) {
        Node<T> *temp = head;
        int count = 0;
        while (count<index) {
            temp = temp->getNext();
            count++;
        }
        return temp->getValue();
    }
    
}

template<typename T>
void LinkedList<T>::print(){
    Node<T> *temp = head;
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

template<typename T>
string LinkedList<T>::getList(){
    Node<T> *temp = head;
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
//     LinkedList<std::string> *list = new LinkedList<std::string>();
//     list->print();
//     list->insertStart("a");
//     list->insertStart("b");
//     list->insertStart("c");
//     list->insertStart("d");
//     list->insertStart("e");
//     cout << "tail: " << list->tail->getValue() << "\n";
//     list->insertEnd("z");
//     cout << "tail: " << list->tail->getValue() << "\n";
//     list->print();
//     list->deleteStart();
//     list->deleteStart();
//     list->deleteStart();
//     list->deleteStart();
//     cout << "tail: " << list->tail->getValue() << "\n";
//     list->print();
//     list->modify("p", 1);
//     list->print();
//     cout << "tail: " << list->tail->getValue() << "\n";
// }