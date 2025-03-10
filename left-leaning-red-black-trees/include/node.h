#ifndef __NODE_1_H
#define __NODE_1_H

#include "color.h"

class Node {
   public:
    int key;
    COLOR color;
    Node* leftChild;
    Node* rightChild;
    Node* parent;
    
    Node(int key) : key(key), color(COLOR::RED), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}

    ~Node() {
        delete leftChild;
        delete rightChild;
    }
};

#endif