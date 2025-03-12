#ifndef _TREE_H
#define _TREE_H

#include <functional>
#include <iostream>

#include "node.hpp"
#include <concepts>

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
        out << "digraph {\n";
        tree.digraph(tree.root, out);
        out << "}";
        return out;
    }

    void add(int k)
    {
        addNode(k);
    }

    template <traversal_order _o>
    void traverse(const std::function<void(const Node<K> *)> &fun) const
    {
        switch (_o)
        {
        case preorder:
            traverse_preorder(root, fun);
            break;
        case inorder:
            traverse_inorder(root, fun);
            break;
        default:
            traverse_postorder(root, fun);
        }
    }

    void remove(int k)
    {
        Node<K> *parent = root;
        Node<K> *node = root;

        while (node != nullptr && node->key != k)
        {
            parent = node;
            node = k <= node->key ? node->leftChild : node->rightChild;
        }

        if (node == nullptr)
        {
            return;
        }
        else if (node->leftChild == nullptr && node->rightChild == nullptr)
        {
            if (parent->leftChild == node)
            {
                parent->leftChild = nullptr;
            }
            else
            {
                parent->rightChild = nullptr;
            }
        }
        else if (node->rightChild == nullptr)
        {
            if (parent->rightChild == node)
            {
                parent->rightChild = node->leftChild;
            }
            else
            {
                parent->leftChild = node->leftChild;
            }
        }
        else if (node->leftChild == nullptr)
        {
            if (parent->leftChild == node)
            {
                parent->leftChild = node->rightChild;
            }
            else
            {
                parent->rightChild = node->rightChild;
            }
        }
        else
        {
            Node<K> *l_parent = node;
            Node<K> *l_node = node->leftChild;

            while (l_node->rightChild != nullptr)
            {
                l_parent = l_node;
                l_node = l_node->rightChild;
            }

            node->key = l_node->key;
            if (l_parent == node)
            {
                l_parent->leftChild = l_node->leftChild;
            }
            else
            {
                l_parent->rightChild = l_node->leftChild;
            }
            node = l_node;
        }

        node->leftChild = nullptr;
        node->rightChild = nullptr;
        delete node;
    };

    Node<int> *find(int k) const
    {
        Node<K> *p = root;
        while (p != nullptr && k != p->key)
            p = k < p->key ? p->leftChild : p->rightChild;
        return p;
    };

    std::vector<K> range(const int &a, const int &b) const
    {
        std::vector<K> v;
        Node<K> *p = root;
        range(a, b, p, v);
        return v;
    };

private:
    void deleteTree(Node<K> *p)
    {
        if (p == nullptr)
            return;
        deleteTree(p->leftChild);
        deleteTree(p->rightChild);
        delete p;
    }

    void addNode(int key)
    {
        Node<K> *parent = root;
        Node<K> *node = root;

        while (node != nullptr)
            if (key <= node->key)
            {
                parent = node;
                node = node->leftChild;
            }
            else
            {
                parent = node;
                node = node->rightChild;
            }

        node = new Node<K>(K(key));
        if (parent != nullptr)
            key <= parent->key ? parent->leftChild = node : parent->rightChild = node;
        else
            root = node;
    }

    void digraph(const Node<K> *p, std::ostream &out) const
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

        digraph(p->leftChild, out);
        digraph(p->rightChild, out);
    }

    void range(const int &a, const int &b, Node<K> *p, std::vector<K> &v) const
    {
        if (p == nullptr)
            return;

        if (p->leftChild != nullptr && p->leftChild->key >= a && p->leftChild->key <= b)
            range(a, b, p->leftChild, v);
        if (p->key >= a && p->key <= b)
            v.push_back(p->key);
        if (p->rightChild != nullptr && p->rightChild->key >= a && p->rightChild->key <= b)
            range(a, b, p->rightChild, v);
    }

    void traverse_preorder(const Node<K> *p, const std::function<void(const Node<K> *)> &fun) const
    {
        if (p == nullptr)
            return;
        fun(p);
        traverse_preorder(p->leftChild, fun);
        traverse_preorder(p->rightChild, fun);
    }

    void traverse_inorder(const Node<K> *p, const std::function<void(const Node<K> *)> &fun) const
    {
        if (p == nullptr)
            return;
        traverse_inorder(p->leftChild, fun);
        fun(p);
        traverse_inorder(p->rightChild, fun);
    }

    void traverse_postorder(const Node<K> *p, const std::function<void(const Node<K> *)> &fun) const
    {
        if (p == nullptr)
            return;
        traverse_postorder(p->leftChild, fun);
        traverse_postorder(p->rightChild, fun);
        fun(p);
    }
};

#endif