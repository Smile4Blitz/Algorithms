#ifndef _TREE_H
#define _TREE_H

#include <functional>
#include <iostream>

#include "node.hpp"

enum traversal_order
{
    inorder,
    preorder,
    postorder
};

template <std::integral K>
class Tree
{

public:
    Node<K> *root = nullptr;

    Tree() {}

    ~Tree()
    {
        delete root;
    }

    friend std::ostream &operator<<(std::ostream &out, const Tree &tree)
    {
        out << "TODO";
        return out;
    }

    void add(K key)
    {
        if (!root)
        {
            root = new Node<K>(key);
            return;
        }

        Node<K> *p = root;
        Node<K> *parent = nullptr;

        while (p != nullptr)
        {
            parent = p;
            p = (key <= p->key) ? p->leftChild : p->rightChild;
        }

        // Insert the new node as a child of the found parent
        if (key <= parent->key)
            parent->leftChild = new Node<K>(key);
        else
            parent->rightChild = new Node<K>(key);
    }

    Node<K> *find(K key)
    {
        Node<K> *p = root;

        while(p != nullptr && p->key != key) {
            p = (key <= p->key) ? p->leftChild : p->rightChild;
        }

        return p;
    }

    void remove(K key)
    {
        Node<K> *p = root;

        while(p != nullptr && p->key != key) {
            p = (key <= p->key) ? p->leftChild : p->rightChild;
        }

        if(p == nullptr)
            return;

        if(p->leftChild != nullptr) {
            // find largest node in left subtree
            Node<K> *left_subtree_largest_node = p->leftChild;

            while(left_subtree_largest_node->rightChild->rightChild != nullptr)
                left_subtree_largest_node = left_subtree_largest_node->rightChild;

            // use value of largest left node as new value for delete node
            p->key = left_subtree_largest_node->rightChild->key;
            Node<K> *toDelete = left_subtree_largest_node->rightChild;

            // if largest left node had left child, move that left child to left largest node old position
            if(left_subtree_largest_node->rightChild->leftChild != nullptr) {
                left_subtree_largest_node->rightChild = left_subtree_largest_node->rightChild->leftChild;
            }

            toDelete->leftChild == nullptr;
            delete toDelete;
        }
    }

    template <traversal_order _o>
    void traverse(const std::function<void(const Node<K> *)> &fun) const
    {
        
    }

    std::vector<K> range(K low, K high) const
    {
        // TODO
    }

private:
    // void add(Node<K> **target, K key)
    // {
    //     // TODO
    // }

    // void remove(Node<K> **target, K key)
    // {
    //     // TODO
    // }

    // Node<K> *find(Node<K> *target, K key)
    // {
    //     // TODO
    // }

    // void range(const Node<K> *target, K low, K high, std::vector<K> &res) const
    // {
    //     // TODO
    // }
};

#endif
