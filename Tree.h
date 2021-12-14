#include <iostream>
#include "list.h"
#include "TreeException.h"

typedef int string;
#define compLT(a, b) (a < b)
#define compEQ(a, b) (a == b)

class RaBTree {
public:
    std::string findTranslate(std::string key) const;
    void print(std::ostream &out);
    void insert(std::string key);
    void deleteElement(std::string elem);

    RaBTree() = default;
    RaBTree(const RaBTree& tree) = delete;
    RaBTree& operator=(const RaBTree&) = delete;

private:
    typedef enum {
        BLACK, RED
    } nodeColor;

    struct Node {
        std::string key_;
        Node *left_;
        Node *right_;
        Node *p_;
        nodeColor color_;
        List &translate_;

        Node(std::string &key, List *tr, Node *left = nullptr, Node *right = nullptr,
             nodeColor color_ = BLACK, Node *p = nullptr) :
                key_(key), translate_(*tr), left_(left), right_(right), color_(color_), p_(p) {}
    };

    Node *root_ = NULL;

    Node *grandparent(Node *ob) const;
    Node *uncle(Node *ob) const;
    Node *sibling(Node *ob) const;
    void rotate_left(RaBTree::Node *x);
    void rotate_right(Node *x);
    void insert_case1(Node *x);
    void insert_case2(Node *x);
    void insert_case3(Node *x);
    void insert_case4(Node *x);
    void insert_case5(Node *x);
    void printNode(std::ostream &out, Node *root);
    Node *findNode(std::string key) const;
    void insPrivate(std::string key, List *tr);
    Node *getSuccessor(Node *node) const;
    Node *getMin(Node *node) const;
    void delete_case(Node *n);
    void deleteFixup(Node *x);
    bool isRus(const char symbol);

};

