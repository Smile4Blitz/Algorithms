#include "tree.h"

Node *LeftLeaningRedBlackTree::rotateLeft(Node *x)
{
    if(x->rightChild == nullptr)
        return x;
    Node *y = x->rightChild;

    x->rightChild = y->leftChild;
    if (y->leftChild != nullptr)
    {
        y->leftChild->parent = x;
    }
    y->parent = x->parent;

    if (y->parent == nullptr)
    {
        root = y;
    }
    else if (y->parent->leftChild == nullptr)
    {
        y->parent->leftChild = y;
    }
    else
    {
        y->parent->rightChild = y;
    }

    y->leftChild = x;
    x->parent = y;

    return y;
}

Node *LeftLeaningRedBlackTree::rotateRight(Node *x)
{
    if(x->leftChild == nullptr)
        return x;
    Node *y = x->leftChild;

    x->leftChild = y->rightChild;
    if(x->leftChild != nullptr) {
        x->leftChild->parent = x;
    }

    y->parent = x->parent;
    if(y->parent == nullptr) {
        root = y;
    } else if (y->parent->leftChild == x) {
        y->parent->leftChild = y;
    } else {
        y->parent->rightChild = y;
    }

    y->rightChild = x;
    x->parent = y;

    return y;
}

bool LeftLeaningRedBlackTree::isRed(Node *node)
{
    return node && (node->color == COLOR::RED);
}

void LeftLeaningRedBlackTree::colorFlip(Node *node)
{
    node->color = this->invertColor(node->color);
}

COLOR LeftLeaningRedBlackTree::invertColor(COLOR color)
{
    if (color == COLOR::BLACK)
    {
        return COLOR::RED;
    }
    return COLOR::BLACK;
}

void LeftLeaningRedBlackTree::drawDotTree(const char *filename)
{
    ofstream out(filename);
    assert(out);
    out << "digraph {" << std::endl;
    int nullcounter = 0;
    drawrecBinairy(out, nullcounter, root);
    out << "}";
    out.close();
}

void LeftLeaningRedBlackTree::drawrecBinairy(ofstream &out, int &nullcounter, Node *node)
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

void LeftLeaningRedBlackTree::insert(int key)
{
    Node *node = new Node(key);
    Node *parent = nullptr;
    Node *current = root;

    while (current != nullptr)
    {
        parent = current;
        if (key < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    node->parent = parent;

    if (!parent)
        root = node;
    else if (key < parent->key)
        parent->leftChild = node;
    else
        parent->rightChild = node;

    // TODO
}

int LeftLeaningRedBlackTree::deleteMin()
{
    // TODO
    return -1;
}

bool LeftLeaningRedBlackTree::contains(int key)
{
    Node *current = root;
    while (current != nullptr)
    {
        if (key == current->key)
            return true;
        else if (key < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return false;
}

void inOrderTraversalHelper(Node *node)
{
    if (node)
    {
        inOrderTraversalHelper(node->leftChild);
        std::cout << node->key << " ";
        inOrderTraversalHelper(node->rightChild);
    }
}

void LeftLeaningRedBlackTree::inOrderTraversal()
{
    inOrderTraversalHelper(root);
    std::cout << std::endl;
}

int getHeightHelper(Node *node)
{
    if (!node)
        return -1;
    int leftHeight = getHeightHelper(node->leftChild);
    int rightHeight = getHeightHelper(node->rightChild);
    return 1 + std::max(leftHeight, rightHeight);
}

int LeftLeaningRedBlackTree::getHeight()
{
    return getHeightHelper(root);
}

void LeftLeaningRedBlackTree::drawTree()
{
    drawTree(root, 0);
}

void LeftLeaningRedBlackTree::drawTree(Node *node, int depth)
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