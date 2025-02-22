#ifndef _TREE_H
#define _TREE_H

#include <functional>
#include <iostream>

#include "node.hpp"

enum traversal_order { inorder, preorder, postorder };

template <std::integral K>
class Tree {

public:

    Node<K>* root = nullptr;

    Tree() {}

    ~Tree() {
        delete root;
    }

    friend std::ostream& operator<<(std::ostream& out, const Tree& tree) {
        out << "TODO";
        return out;
    }

    // TODO
    //
    // - add
    // - traverse<traversal_order>
    // - remove
    // - find
    // - range

private:

    // ...

};

#endif
