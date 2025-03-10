#ifndef __RED_BLACK_TREE_H
#define __RED_BLACK_TREE_H

#include <iostream>
#include "node.h"

#include <cassert>
#include <fstream>

using std::cerr;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;

class LeftLeaningRedBlackTree {
private:
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void restoreRedBlackProperty(Node* newNode);
    bool isRed(Node* node);
    void colorFlip(Node* node);
    COLOR invertColor(COLOR color);
    void drawrecBinairy(ofstream& out, int& nullcounter, Node* node);
    void drawTree(Node* node, int depth);
    
public:
    Node* root;
    LeftLeaningRedBlackTree() : root(nullptr) {}

    bool contains(int key);
    void insert(int key);
    int deleteMin();
    void inOrderTraversal();
    int getHeight();
    void drawDotTree(const char* filename);
    void drawTree();

    ~LeftLeaningRedBlackTree() {
        delete root;
    }
};

#endif