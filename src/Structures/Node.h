#ifndef NODE
#define NODE

class Node {
    private:
         int value;
         Node *next = nullptr;
        
    public:
        Node(int value);
        int getValue();
        void setValue(int value);
        Node * getNext();
        void setNext(Node* next);
};

#endif