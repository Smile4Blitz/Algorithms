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
        { // If the tree is empty, create root
            root = new Node<K>(key);
            return;
        }

        Node<K> *p = root;
        Node<K> *parent = nullptr; // To track the parent node

        // Traverse to the correct insertion point
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
        // TODO
    }

    void remove(K key)
    {
        // TODO
    }

    template <traversal_order _o>
    void traverse(const std::function<void(const Node<K> *)> &fun) const
    {
        // TODO
    }

    std::vector<K> range(K low, K high) const
    {
        // TODO
    }

private:
    void add(Node<K> **target, K key)
    {
        // TODO
    }

    void remove(Node<K> **target, K key)
    {
        // TODO
    }

    Node<K> *find(Node<K> *target, K key)
    {
        // TODO
    }

    void range(const Node<K> *target, K low, K high, std::vector<K> &res) const
    {
        // TODO
    }
};

#endif
