#include "list.h"

List::~List() {
    Node *x = nullptr;
    while (head_ != nullptr) {
        x = head_->next_;
        delete head_;
        head_ = x;
    }
};

void List::insertHead(std::string item_) {
    Node *x = new Node(item_, nullptr, nullptr);
    insertHead(x);
}

void List::insertTail(std::string item_) {
    Node *x = new Node(item_, nullptr, nullptr);
    insertTail(x);
}

void List::insertTail(Node *x) {
    x->prev_ = tail_;
    if (tail_ != nullptr) {
        tail_->next_ = x;
    } else {
        head_ = x;
    }
    tail_ = x;
    count_++;
}

void List::insertHead(Node *x) {
    x->next_ = head_;
    if (head_ != nullptr) {
        head_->prev_ = x;
    } else {
        tail_ = x;
    }
    head_ = x;
    count_++;
}

void List::insert(std::string ob) {
    while (ob.find(",") != -1) {
        char point = ob.find(",");
        if (point == ob.length() - 1) {
            ob.erase(point - 1, point);
            break;
        }
        std::string str = ob.substr(0, point);
        insert(str);
        ob.erase(0, point + 2);
    }
    if (count_ == 0) {
        insertHead(ob);
    } else if (count_ == 1) {
        bool isWas1 = false;
        if (head_->item_ == ob)
            isWas1 = true;
        if (isWas1 == false) {
            if (ob < this->head_->item_) {
                insertHead(ob);
            } else {
                insertTail(ob);
            }
        }
    } else if (count_ > 1) {
        bool isWas2 = false;
        Node *tempNode = head_;
        std::string temp = "";
        while (tempNode != nullptr) {
            temp = tempNode->item_;
            if (ob == temp) {
                isWas2 = true;
            }
            tempNode = tempNode->next_;
        }
        if (isWas2 == false) {
            if (ob < this->head_->item_) {
                insertHead(ob);
            } else if (ob > this->tail_->item_) {
                insertTail(ob);
            } else {
                Node *newOb = new Node(ob);
                Node *x = head_;
                Node *prev_ = new Node("");
                while (x != nullptr && ob > x->item_) {
                    prev_ = x;
                    x = x->next_;
                }
                prev_->next_ = newOb;
                newOb->next_ = x;
                newOb->prev_ = prev_;
                x->prev_ = newOb;
                count_++;
            }
        }
    }
};

void List::print(std::ostream &out) const {
    Node *temp = head_;
    while (temp != nullptr) {
        out << " " << temp->item_ << ";";
        temp = temp->next_;
    }

}

std::string List::toStr() {

    std::string str;
    Node *temp = head_;
    str += " - ";
    while (temp != nullptr) {
        str += temp->item_;
        str += "; ";
        temp = temp->next_;
    }
    return str;
}