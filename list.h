#include<iostream>


class List
{
public:
    List() : count_(0), head_(nullptr), tail_(nullptr) {}
    ~List();

    void insertHead(std::string item_);
    void insertTail(std::string item_);
    void insert(std::string ob);
    void print(std::ostream& out) const;
    std::string toStr();

private:
    struct Node
    {
        std::string item_;
        Node* next_;
        Node* prev_;
        Node(std::string item, Node* next = nullptr, Node* prev = nullptr)
        {
            this->item_ = item;
            this->next_ = next;
            this->prev_ = prev;
        }
    };
    Node* head_;
    Node* tail_;
    int count_;
    void insertTail(Node* x);
    void insertHead(Node* x);

};


