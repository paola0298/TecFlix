#ifndef NODE
#define NODE

template<typename T>

class Node {
    private:
         T value;
         Node<T> *next = nullptr;
        
    public:
        Node(T value);
        T getValue();
        void setValue(T value);
        Node<T> * getNext();
        void setNext(Node<T>* next);
};

#endif