#include "redBlackTree.h"

RedBlackTree::~RedBlackTree()
{
    deleteTree(root);
}

void RedBlackTree::deleteTree(Node *p)
{
    if (p->leftChild != nullptr)
        deleteTree(p->leftChild);
    if (p->rightChild != nullptr)
        deleteTree(p->rightChild);
    delete p;
}

void RedBlackTree::insert(int key)
{
    // INSERT NODE AS RED LEAF
    if (root == nullptr)
    {
        root = new Node(key);
        root->color = COLOR::BLACK;
        return;
    }

    Node *p_parent = root;
    Node *p_node = root;
    while (p_node != nullptr)
    {
        p_parent = p_node;
        p_node = key <= p_node->key ? p_node->leftChild : p_node->rightChild;
    }

    p_node = new Node(key);
    p_node->parent = p_parent;
    if (key <= p_parent->key)
    {
        p_parent->leftChild = p_node;
    }
    else
    {
        p_parent->rightChild = p_node;
    }

    // START FIXING RB-PROPERTIES
    FixRBProperties(p_node);
}

void RedBlackTree::FixRBProperties(Node *p)
{
    // root is always black so there will always be a parent & grandparent
    while (p->color == COLOR::RED && p->parent != nullptr && p->parent->color == COLOR::RED)
    {
        Node *p_parent = p->parent;
        Node *p_grandparent = p->parent->parent;
        Node *p_uncle = (p_grandparent->leftChild == p_parent) ? p_grandparent->rightChild : p_grandparent->leftChild;

        if (p_uncle != nullptr && p_uncle->color == COLOR::RED)
        {
            p_parent->color = COLOR::BLACK;
            p_grandparent->color = (p_grandparent != root) ? COLOR::RED : COLOR::BLACK;
            p_uncle->color = COLOR::BLACK;
            p = p_grandparent;
        }
        else
        {
            if (p->key <= p_grandparent->key && p_parent->rightChild == p)
            {
                rotateLeft(p);
                std::swap(p, p_parent);
            }
            else if (p->key > p_grandparent->key && p_parent->leftChild == p)
            {
                rotateRight(p);
                std::swap(p, p_parent);
            }

            if (p_grandparent->rightChild != p_parent)
            {
                rotateRight(p_parent);
                p_parent->color = COLOR::BLACK;
                p_grandparent->color = COLOR::RED;
            }
            else
            {
                rotateLeft(p_parent);
                p_parent->color = COLOR::BLACK;
                p_grandparent->color = COLOR::RED;
            }
        }
    }
}

void RedBlackTree::rotateLeft(Node *p)
{
    Node *p_parent = p->parent;
    if (p_parent == nullptr)
    {
        p->color = COLOR::BLACK;
        return;
    }

    Node *p_grandparent = (p_parent != nullptr) ? p_parent->parent : nullptr;
    if (p_grandparent != nullptr)
    {
        if (p_grandparent->leftChild == p_parent)
            p_grandparent->leftChild = p;
        else if (p_grandparent->rightChild == p_parent)
            p_grandparent->rightChild = p;
    }
    else
    {
        root = p;
    }

    p_parent->rightChild = p->leftChild;
    p->leftChild = p_parent;
    p_parent->parent = p;
    p->parent = p_grandparent;
}

void RedBlackTree::rotateRight(Node *p)
{
    Node *p_parent = p->parent;
    if (p_parent == nullptr)
    {
        p->color = COLOR::BLACK;
        return;
    }

    Node *p_grandparent = (p_parent != nullptr) ? p_parent->parent : nullptr;
    if (p_grandparent != nullptr)
    {
        if (p_grandparent->leftChild == p_parent)
            p_grandparent->leftChild = p;
        else if (p_grandparent->rightChild == p_parent)
            p_grandparent->rightChild = p;
    }
    else
    {
        root = p;
    }

    p_parent->leftChild = p->rightChild;
    p->rightChild = p_parent;
    p_parent->parent = p;
    p->parent = p_grandparent;
}

bool RedBlackTree::contains(int key)
{
    Node *p = root;
    while (p != nullptr && p->key != key)
        p = key <= p->key ? p->leftChild : p->rightChild;
    return p != nullptr;
}

void RedBlackTree::inOrderTraversal()
{
    traverse_inorder(root);
    std::cout << std::endl;
}

void RedBlackTree::traverse_inorder(const Node *p) const
{
    if (p == nullptr)
        return;
    traverse_inorder(p->leftChild);
    std::cout << " " << p->key << " ";
    traverse_inorder(p->rightChild);
}

int RedBlackTree::getHeight()
{
    // height is: root -> leaf (nodes including root)
    // height is: root -> nil (vertices)
    // return height(root);

    // height is: root -> leaf (nodes excluding root)
    // height is: root -> leaf (vertices)
    return height(root) - 1;
}

int RedBlackTree::height(const Node *p) const
{
    if (p == nullptr)
        return 0;
    int leftHeight = height(p->leftChild);
    int rightHeight = height(p->rightChild);
    return (leftHeight >= rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

/**
 * issue with parent pointer pointing at grandparent sometimes
 */
void RedBlackTree::deleteNode(int key)
{
    Node *p = root;
    while (p != nullptr && p->key != key)
    {
        p = (key <= p->key) ? p->leftChild : p->rightChild;
    }

    if (p == nullptr)
    {
        return;
    }

    if (p->parent == nullptr)
    {
        root = nullptr;
        delete p;
        return;
    }

    Node *p_parent = p->parent;
    if (p->leftChild == nullptr && p->rightChild == nullptr)
    {
        if (p_parent->leftChild == p)
        {
            p_parent->leftChild = nullptr;
        }
        else
        {
            p_parent->rightChild = nullptr;
        }
    }
    else if (p->leftChild != nullptr && p->rightChild != nullptr)
    {
        Node *toDelete = p->leftChild;
        while (toDelete->rightChild != nullptr)
        {
            toDelete = toDelete->rightChild;
        }

        p->key = toDelete->key;
        if (toDelete->leftChild != nullptr)
        {
            toDelete->leftChild->parent = toDelete->parent;
        }

        if (toDelete->parent->rightChild == toDelete)
        {
            toDelete->parent->rightChild = toDelete->leftChild;
        }
        else
        {
            toDelete->parent->leftChild = toDelete->leftChild;
        }
        p = toDelete;
        FixRBProperties(toDelete->parent->rightChild);
    }
    else
    {
        Node *newChild = (p->leftChild != nullptr) ? p->leftChild : p->rightChild;
        newChild->parent = p_parent;
        if (p_parent->leftChild == p)
        {
            p_parent->leftChild = newChild;
        }
        else
        {
            p_parent->rightChild = newChild;
        }
        FixRBProperties(newChild);
    }

    p->parent = nullptr;
    p->leftChild = nullptr;
    p->rightChild = nullptr;
    delete p;
}

void RedBlackTree::drawTree()
{
    drawTree(root, 0);
}

void RedBlackTree::drawTree(Node *node, int depth)
{
    std::string prefix = "     ";

    if (node->color == COLOR::BLACK)
    {
        std::cout << BOLDBLUE << node->key << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << node->key << RESET << std::endl;
    }

    if (node->leftChild)
    {
        for (int i = 0; i < depth; i++)
        {
            std::cout << prefix;
        }
        std::cout << "Left ->";
        drawTree(node->leftChild, depth + 1);
    }
    if (node->rightChild)
    {
        for (int i = 0; i < depth; i++)
        {
            std::cout << prefix;
        }
        std::cout << "Right ->";
        drawTree(node->rightChild, depth + 1);
    }
}

void RedBlackTree::drawDotTree(const char *filename)
{
    ofstream out(filename);
    assert(out);
    out << "digraph {" << std::endl;
    int nullcounter = 0;
    drawrecBinairy(out, nullcounter, root);
    out << "}";
    out.close();
}

void RedBlackTree::drawrecBinairy(ofstream &out, int &nullcounter, Node *node)
{
    if (node)
    {
        out << "    " << node->key << " [label=\"" << node->key << "\"";
        if (node->color == COLOR::RED)
        {
            out << ", fillcolor=red, style=filled";
        }
        else if (node->color == COLOR::BLACK)
        {
            out << ", fillcolor=black, style=filled, fontcolor=white";
        }
        out << "];" << std::endl;
        if (node->leftChild)
        {
            out << "    " << node->key << " -> " << node->leftChild->key << ";" << std::endl;
            drawrecBinairy(out, nullcounter, node->leftChild);
        }
        else
        {
            out << "    null" << nullcounter << " [shape=point];" << std::endl;
            out << "    " << node->key << " -> null" << nullcounter << ";" << std::endl;
            nullcounter++;
        }
        if (node->rightChild)
        {
            out << "    " << node->key << " -> " << node->rightChild->key << ";" << std::endl;
            drawrecBinairy(out, nullcounter, node->rightChild);
        }
        else
        {
            out << "    null" << nullcounter << " [shape=point];" << std::endl;
            out << "    " << node->key << " -> null" << nullcounter << ";" << std::endl;
            nullcounter++;
        }
    }
}