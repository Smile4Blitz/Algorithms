#ifndef _NODE_H
#define _NODE_H

template <std::integral K>
class Node {

public:

    K key;
    Node* leftChild = nullptr;
    Node* rightChild = nullptr;

    Node(K _key) : key(_key) {}

};

#endif
