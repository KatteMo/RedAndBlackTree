#include "Tree.h"

RaBTree::Node *RaBTree::grandparent(RaBTree::Node *ob) const {
    if ((ob != NULL) && (ob->p_ != NULL))
        return ob->p_->p_;
    else
        return NULL;
}

RaBTree::Node *RaBTree::uncle(RaBTree::Node *ob) const {
    Node *g = grandparent(ob);
    if (g == NULL)
        return NULL;
    if (ob->p_ == g->left_)
        return g->right_;
    else
        return g->left_;
}

RaBTree::Node *RaBTree::sibling(RaBTree::Node *ob) const {
    if (ob == ob->p_->left_)
        return ob->p_->right_;
    else
        return ob->p_->left_;
}

void RaBTree::rotate_left(RaBTree::Node *x) {

    Node *y = x->right_;

    x->right_ = y->left_;
    if (y->left_ != NULL) y->left_->p_ = x;

    if (y != NULL) y->p_ = x->p_;
    if (x->p_) {
        if (x == x->p_->left_)
            x->p_->left_ = y;
        else
            x->p_->right_ = y;
    } else {
        root_ = y;
    }

    y->left_ = x;
    if (x != NULL) x->p_ = y;
}

void RaBTree::rotate_right(RaBTree::Node *x) {
    Node *y = x->left_;

    x->left_ = y->right_;
    if (y->right_ != NULL) y->right_->p_ = x;

    if (y != NULL) y->p_ = x->p_;
    if (x->p_) {
        if (x == x->p_->right_)
            x->p_->right_ = y;
        else
            x->p_->left_ = y;
    } else {
        root_ = y;
    }

    y->right_ = x;
    if (x != NULL) x->p_ = y;
}

void RaBTree::insert_case1(RaBTree::Node *x) {
    if (x->p_ == NULL)
        x->color_ = BLACK;
    else
        insert_case2(x);
}

void RaBTree::insert_case2(RaBTree::Node *x) {
    if (x->p_->color_ == BLACK)
        return;
    else
        insert_case3(x);
}

void RaBTree::insert_case3(RaBTree::Node *x) {
    Node *u = uncle(x), *g;

    if ((u != NULL) && (u->color_ == RED)) {
        x->p_->color_ = BLACK;
        u->color_ = BLACK;
        g = grandparent(x);
        g->color_ = RED;
        insert_case1(g);
    } else {
        insert_case4(x);
    }
}

void RaBTree::insert_case4(RaBTree::Node *x) {
    Node *g = grandparent(x);

    if ((x == x->p_->right_) && (x->p_ == g->left_)) {
        rotate_left(x->p_);

        x = x->left_;
    } else if ((x == x->p_->left_) && (x->p_ == g->right_)) {
        rotate_right(x->p_);

        x = x->right_;
    }
    insert_case5(x);
}

void RaBTree::insert_case5(RaBTree::Node *x) {
    Node *g = grandparent(x);

    x->p_->color_ = BLACK;
    g->color_ = RED;
    if ((x == x->p_->left_) && (x->p_ == g->left_)) {
        rotate_right(g);
    } else {
        rotate_left(g);
    }
}

void RaBTree::printNode(std::ostream &out, RaBTree::Node *root) {
    if (root) {
        out << '(';
        out << root->key_ << ' ' << root->color_;
        root->translate_.print(std::cout);
        printNode(out, root->left_);
        printNode(out, root->right_);
        out << ')';
    }
};

RaBTree::Node *RaBTree::findNode(std::string key) const {
    Node *current = root_;
    while (current != NULL) {
        if (compEQ(key, current->key_))
            return (current);
        else
            current = compLT(key, current->key_) ? current->left_ : current->right_;
    }
    return 0;
}

void RaBTree::insPrivate(std::string key, List *tr) {
    Node *current;
    Node *parent;

    current = root_;
    parent = 0;
    while (current != NULL) {
        parent = current;
        current = compLT(key, current->key_) ? current->left_ : current->right_;
    }

    Node *x = new Node(key, tr);
    x->p_ = parent;
    x->left_ = NULL;
    x->right_ = NULL;
    x->color_ = RED;

    if (parent) {
        if (compLT(key, parent->key_))
            parent->left_ = x;
        else
            parent->right_ = x;
    } else {
        root_ = x;
    }

    insert_case1(x);
}

RaBTree::Node *RaBTree::getSuccessor(RaBTree::Node *node) const {
    if (node->right_ != nullptr) {
        return getMin(node->right_);
    }
    Node *temp = node->p_;
    while (temp != nullptr && node == temp->right_) {
        node = temp;
        temp = temp->p_;
    }
    return temp;
};

RaBTree::Node *RaBTree::getMin(RaBTree::Node *node) const {
    while (node->left_ != nullptr) {
        node = node->left_;
    }
    return node;
};

void RaBTree::delete_case(RaBTree::Node *n) {
    Node *s = sibling(n);

    s->color_ = n->p_->color_;
    n->p_->color_ = BLACK;

    if (n == n->p_->left_) {
        s->right_->color_ = BLACK;
        rotate_left(n->p_);
    } else {
        s->left_->color_ = BLACK;
        rotate_right(n->p_);
    }
}


void RaBTree::deleteFixup(RaBTree::Node *x) {
    while (x != root_ && x->color_ == BLACK) {
        if (x == x->p_->left_) {
            Node *w = x->p_->right_;
            if (w->color_ == RED) {
                w->color_ = BLACK;
                x->p_->color_ = RED;
                rotate_left(x->p_);
                w = x->p_->right_;
            }
            if ((w->left_ == nullptr && w->right_ == nullptr)) {
                w->color_ = RED;
                x = x->p_;
            } else if (w->left_->color_ == BLACK && w->right_->color_ == BLACK) {
                w->color_ = RED;
                x = x->p_;
            } else {
                if (w->right_->color_ == BLACK) {
                    w->left_->color_ = BLACK;
                    w->color_ = RED;
                    rotate_right(w);
                    w = x->p_->right_;
                }
                w->color_ = x->p_->color_;
                x->p_->color_ = BLACK;
                w->right_->color_ = BLACK;
                rotate_left(x->p_);
                x = root_;
            }
        } else {
            Node *w = x->p_->left_;
            if (w->color_ == RED) {
                w->color_ != BLACK;
                x->p_->color_ = RED;
                rotate_right(x->p_);
                w = x->p_->left_;
            }
            if (w->left_ == nullptr && w->right_ == nullptr) {
                w->color_ = RED;
                x = x->p_;
            } else if (w->right_->color_ == BLACK && w->left_->color_ == BLACK) {
                w->color_ = RED;
                x = x->p_;
            } else {
                if (w->left_->color_ == BLACK) {
                    w->right_->color_ = BLACK;
                    w->color_ = RED;
                    rotate_left(w);
                    w = x->p_->left_;
                }
                w->color_ = x->p_->color_;
                x->p_->color_ = BLACK;
                w->left_->color_ = BLACK;
                rotate_right(x->p_);
                x = root_;
            }
        }
    }
    x->color_ = BLACK;
}

bool RaBTree::isRus(const char symbol)
{
    std::string letters =
            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    for (auto letter : letters)
    {
        if (symbol == letter)
        {
            return true;
        }
    }
    return false;
}


std::string RaBTree::findTranslate(std::string key) const {
    Node *node = findNode(key);
    if (!node) {
        throw FoundError(key);
    }
    std::string temp = (key + node->translate_.toStr());
    return temp;
}

void RaBTree::print(std::ostream &out) {
    printNode(out, root_);
    out << std::endl;
}

void RaBTree::insert(std::string key) {
    int point = key.find("-");
    std::string item = key.substr(0, point - 1);
    for (int i = 0; i < item.length(); ++i) {
        char s = item[i];
        if (s < 'A' || s > 'z') {
            throw WordError(item);
        }
    }

    List *tr = new List;
    std::string data = key.substr(point + 2, key.length());

    for (auto symbol : data)
    {
        if (!isRus(symbol) && symbol != ' ' && symbol != ',' && symbol != '(' &&
            symbol != ')' && symbol != '/')
        {
            throw FalseTranlanion(data);
        }
    }

    Node *node = findNode(item);
    if (node != NULL) {
        node->translate_.insert(data);
    } else {
        tr->insert(data);
        insPrivate(item, tr);
    }

}

void RaBTree::deleteElement(std::string elem) {
    Node *node = findNode(elem);
    if (node == NULL)
        throw FoundError(elem);
    Node *y = nullptr;
    Node *x = nullptr;

    if (node->p_ == nullptr) {
        if (node->left_ == nullptr || node->right_ == nullptr) {
            y = node;
        } else {
            y = getSuccessor(node);
            if ((y->p_->right_ != nullptr && y == y->p_->left_) ||
                (y->p_->left_ != nullptr && y == y->p_->right_)) {
                Node *s = sibling(y);
                if (s != nullptr && (s->color_ == BLACK && ((s->left_ != nullptr && s->left_->color_ == RED)
                                                            || (s->right_ != nullptr && s->right_->color_ == RED))))
                    delete_case(y);
            } else
                deleteFixup(y);
        }

        if (y->left_ != nullptr) {
            x = y->left_;
        } else {
            x = y->right_;
        }

        if (x != nullptr) {
            x->p_ = y->p_;
        }
        if (y->p_ == nullptr) {
            root_ = x;
        } else {
            if (y == y->p_->left_) {
                y->p_->left_ = x;
            } else {
                y->p_->right_ = x;
            }
        }

        if (y != node) {
            node->key_ = y->key_;
            node->translate_ = y->translate_;
        }
    } else if (node->left_ == nullptr && node->right_ == nullptr && node->color_ == RED) {
        y = node;
        if (y == y->p_->left_) {
            y->p_->left_ = x;
        } else {
            y->p_->right_ = x;
        }

    } else {
        Node *s = sibling(node);
        if (node->left_ == nullptr && node->right_ == nullptr
            && node->color_ == BLACK && s->left_ == nullptr && s->right_ == nullptr) {
            y = node;
            deleteFixup(node);
            if (y == y->p_->left_) {
                y->p_->left_ = x;
            } else {
                y->p_->right_ = x;
            }
        } else {
            if (node->left_ == nullptr || node->right_ == nullptr) {
                y = node;
            } else {
                y = getSuccessor(node);
            }

            if (y->left_ != nullptr) {
                x = y->left_;
            } else {
                x = y->right_;
            }

            if (x != nullptr) {
                x->p_ = y->p_;
            }

            if (y->p_ == nullptr) {
                root_ = x;
            } else {
                Node *s = sibling(y);
                if (s->color_ == BLACK && ((s->left_ != nullptr && s->left_->color_ == RED && s->right_ == nullptr)
                                           || (s->right_ != nullptr && s->right_->color_ == RED && s->left_ == nullptr))) {
                    delete_case(y);
                    if (y == y->p_->left_) {
                        y->p_->left_ = x;
                    } else {
                        y->p_->right_ = x;
                    }
                } else {
                    deleteFixup(y);
                    if (y == y->p_->left_) {
                        y->p_->left_ = x;
                    } else {
                        y->p_->right_ = x;
                    }
                }
            }

            if (y != node) {
                node->key_ = y->key_;
                node->translate_ = y->translate_;
            }
        }
    }
}
