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
        if (root == nullptr)
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

        while (p != nullptr && p->key != key)
        {
            p = (key <= p->key) ? p->leftChild : p->rightChild;
        }

        return p;
    }

    void remove(K key)
    {
        Node<K> *p = root;
        Node<K> *p_parent = p;
        Node<K> *toDelete = nullptr;

        while (p != nullptr && p->key != key)
        {
            p_parent = p;
            p = (key <= p->key) ? p->leftChild : p->rightChild;
        }

        // key not in tree
        if (p == nullptr)
        {
            return;
        }

        // delete by replacement
        if (p->leftChild != nullptr)
        {
            // find largest node in left subtree
            Node<K> *node_parent = p;
            Node<K> *node = p->leftChild;

            while (node->rightChild != nullptr)
            {
                node_parent = node;
                node = node->rightChild;
            }

            // replace deleted key value with largest node from left subtree
            p->key = node->key;
            toDelete = node;

            // if largest node in left subtree has a left child, have it take the largest node pos
            if (node_parent != p)
            {
                node_parent->rightChild = (node->leftChild != nullptr) ? node->leftChild : nullptr;
            }
            else
            {
                node_parent->leftChild = (node->leftChild != nullptr) ? node->leftChild : nullptr;
            }
        }
        else if (p->rightChild != nullptr)
        {
            // find smallest node in right tree
            Node<K> *node_parent = p;
            Node<K> *node = p->rightChild;

            while (node->leftChild != nullptr)
            {
                node_parent = node;
                node = node->leftChild;
            }

            // replace deleted key value with smallest node from right subtree
            p->key = node->key;
            toDelete = node;

            if (node_parent != p)
            {
                node_parent->leftChild = (node->rightChild != nullptr) ? node->rightChild : nullptr;
            }
            else
            {
                node_parent->rightChild = (node->rightChild != nullptr) ? node->rightChild : nullptr;
            }
            // if smallest node in right subtree has a right child, have it take the smallest node pos
            node_parent->leftChild = (node->rightChild != nullptr) ? node->rightChild : nullptr;
        }
        else
        {
            // key to delete is leaf node
            toDelete = p;
            if(p_parent->leftChild == p) {
                p_parent->leftChild == nullptr;
            } else {
                p_parent->rightChild == nullptr;
            }
        }

        toDelete->leftChild = nullptr;
        toDelete->rightChild = nullptr;
        delete toDelete;
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
