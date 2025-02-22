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

    friend std::ostream &operator<<(std::ostream &out, const Tree<K> &tree)
    {
        out << "digraph {\n";
        tree.digraph(out, tree.root);
        out << "}";
        return out;
    }

    void digraph(std::ostream &out, const Node<K> *p) const
    {
        if (p == nullptr)
            return;

        if (p->leftChild != nullptr)
        {
            out << p->key << " -> " << p->leftChild->key << "\n";
        }
        if (p->rightChild != nullptr)
        {
            out << p->key << " -> " << p->rightChild->key << "\n";
        }
        digraph(out, p->leftChild);
        digraph(out, p->rightChild);
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
            if (p_parent->leftChild == p)
            {
                p_parent->leftChild == nullptr;
            }
            else
            {
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
        if (_o == inorder)
        {
            traverse_in_order(root, fun);
        }
        else if (_o == preorder)
        {
            traverse_pre_order(root, fun);
        }
        else
        {
            traverse_post_order(root, fun);
        }
    }

    std::vector<K> range(K low, K high) const
    {
        std::vector<K> v;
        range(root, low, high, v);
        return v;
    }

private:
    void traverse_in_order(const Node<K> *p, const std::function<void(const Node<K> *)> &fun) const
    {
        if (p == nullptr)
            return;

        if (p->leftChild != nullptr)
            traverse_in_order(p->leftChild, fun);

        fun(p);

        if (p->rightChild != nullptr)
            traverse_in_order(p->rightChild, fun);
    }
    void traverse_pre_order(const Node<K> *p, const std::function<void(const Node<K> *)> &fun) const
    {
        if (p == nullptr)
            return;

        fun(p);

        if (p->leftChild != nullptr)
            traverse_pre_order(p->leftChild, fun);

        if (p->rightChild != nullptr)
            traverse_pre_order(p->rightChild, fun);
    }
    void traverse_post_order(const Node<K> *p, const std::function<void(const Node<K> *)> &fun) const
    {
        if (p == nullptr)
            return;

        if (p->leftChild != nullptr)
            traverse_post_order(p->leftChild, fun);

        if (p->rightChild != nullptr)
            traverse_post_order(p->rightChild, fun);

        fun(p);
    }

    void range(const Node<K> *target, const K &low, const K &high, std::vector<K> &res) const
    {
        if (target == nullptr)
            return;

        if (target->key > low)
            range(target->leftChild, low, high, res);

        if (target->key >= low && target->key <= high)
            res.push_back(target->key);

        if (target->key < high)
            range(target->rightChild, low, high, res);
    }
};

#endif
