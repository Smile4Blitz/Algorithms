#ifndef __RED_BLACK_TREE_H
#define __RED_BLACK_TREE_H

#include <iostream>
#include "node.h"

#include <cassert>
#include <fstream>
#include <algorithm>

using std::cerr;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;

class RedBlackTree
{
private:
    void drawrecBinairy(ofstream &out, int &nullcounter, Node *node);
    void drawTree(Node *node, int depth);

    void traverse_inorder(const Node *) const;
    void deleteTree(Node *p);

    void FixRBProperties(Node *p);
    void rotateLeft(Node *p);
    void rotateRight(Node *p);

    int height(const Node *) const;
public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree();

    Node *root;

    void insert(int key);
    void deleteNode(int key);
    bool contains(int key);
    void inOrderTraversal();
    int getHeight();

    void drawDotTree(const char *filename);
    void drawTree();
};

#endif
