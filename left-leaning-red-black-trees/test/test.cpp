#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "tree.h"

bool checkLeftLeaningRedBlackProperty(Node *node)
{
    bool result = true;

    if (!node->parent)
    {
        // the root should be black
        if (node->color == COLOR::RED)
        {
            return false;
        }
        if (node->leftChild)
        {
            result &= checkLeftLeaningRedBlackProperty(node->leftChild);
        }

        if (node->rightChild)
        {
            result &= checkLeftLeaningRedBlackProperty(node->rightChild);
        }
    }
    else if (node->color == COLOR::RED)
    {
        // a red node can only have black children
        if (node->leftChild)
        {
            if (node->leftChild->color == COLOR::RED)
            {
                return false;
            }
            result &= checkLeftLeaningRedBlackProperty(node->leftChild);
        }
        if (node->rightChild)
        {
            if (node->rightChild->color == COLOR::RED)
            {
                return false;
            }
            result &= checkLeftLeaningRedBlackProperty(node->rightChild);
        }
    }
    else
    {
        // a black node should only have red children on its left
        if (node->rightChild)
        {
            if (node->rightChild->color == COLOR::RED)
            {
                return false;
            }
            result &= checkLeftLeaningRedBlackProperty(node->rightChild);
        }
        if (node->leftChild)
        {
            result &= checkLeftLeaningRedBlackProperty(node->leftChild);
        }
    }

    return result;
}

TEST_CASE("leftLeaningRedBlackTreeTest")
{
    LeftLeaningRedBlackTree tree;
    int points[10] = {4, 7, 12, 15, 3, 5, 14, 18, 16, 17};
    for (int i : points)
    {
        tree.insert(i);
    }

    REQUIRE(tree.root != nullptr);
    if (tree.root != nullptr)
    {
        REQUIRE(tree.getHeight() == 3);
        REQUIRE(checkLeftLeaningRedBlackProperty(tree.root));
    }

    for (int i : points)
    {
        REQUIRE(tree.contains(i));
    }

    tree.deleteMin();
    tree.deleteMin();
    tree.deleteMin();

    REQUIRE(checkLeftLeaningRedBlackProperty(tree.root));
    REQUIRE(tree.contains(3) == false);
    REQUIRE(tree.contains(4) == false);
    REQUIRE(tree.contains(5) == false);
}