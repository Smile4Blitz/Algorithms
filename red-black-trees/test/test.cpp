#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "redBlackTree.h"

bool checkRedBlackProperty(Node* node) {
    bool result = true;

    if (!node->parent) {
        // the root should be black
        if (node->color == COLOR::RED) {
            return false;
        }
        result &= checkRedBlackProperty(node->leftChild);
        result &= checkRedBlackProperty(node->rightChild);
    } else if (node->color == COLOR::RED) {
        // a red node can only have black children
        if (node->leftChild) {
            if (node->leftChild->color == COLOR::RED) {
                return false;
            }
            result &= checkRedBlackProperty(node->leftChild);
        }
        if (node->rightChild) {
            if (node->rightChild->color == COLOR::RED) {
                return false;
            }
            result &= checkRedBlackProperty(node->rightChild);
        }
    }

    return result;
}

TEST_CASE("Rotate_left") {
    RedBlackTree tree;
    int points[3] = {4, 7, 12};
    for (int i : points) {
        tree.insert(i);
    }

    REQUIRE(tree.root != nullptr);

    if (tree.root != nullptr) {
        REQUIRE(tree.root->key == 7);
        REQUIRE(tree.root->color == COLOR::BLACK);
        REQUIRE(tree.root->parent == nullptr);

        REQUIRE(tree.root->leftChild->key == 4);
        REQUIRE(tree.root->leftChild->color == COLOR::RED);
        REQUIRE(tree.root->leftChild->parent == tree.root);

        REQUIRE(tree.root->rightChild->key == 12);
        REQUIRE(tree.root->rightChild->color == COLOR::RED);
        REQUIRE(tree.root->rightChild->parent == tree.root);

        REQUIRE(tree.getHeight() == 1);
        REQUIRE(checkRedBlackProperty(tree.root));
    }
}

TEST_CASE("Rotate_right") {
    RedBlackTree tree;
    int points[7] = {4, 7, 12, 15, 3, 5, 14};
    for (int i : points) {
        tree.insert(i);
    }

    REQUIRE(tree.root != nullptr);

    if (tree.root != nullptr) {
        REQUIRE(tree.root->key == 7);
        REQUIRE(tree.root->color == COLOR::BLACK);
        REQUIRE(tree.root->parent == nullptr);

        REQUIRE(tree.root->rightChild->key == 14);
        REQUIRE(tree.root->rightChild->color == COLOR::BLACK);
        REQUIRE(tree.root->rightChild->parent == tree.root);

        REQUIRE(tree.root->rightChild->leftChild->key == 12);
        REQUIRE(tree.root->rightChild->leftChild->color == COLOR::RED);
        REQUIRE(tree.root->rightChild->leftChild->parent ==
                tree.root->rightChild);

        REQUIRE(tree.root->rightChild->rightChild->key == 15);
        REQUIRE(tree.root->rightChild->rightChild->color == COLOR::RED);
        REQUIRE(tree.root->rightChild->rightChild->parent ==
                tree.root->rightChild);

        REQUIRE(tree.getHeight() == 2);
        REQUIRE(checkRedBlackProperty(tree.root));
    }

    for (int i : points) {
        REQUIRE(tree.contains(i));
    }
}

TEST_CASE("large_tree") {
    RedBlackTree tree;
    int points[10] = {4, 7, 12, 15, 3, 5, 14, 18, 16, 17};
    for (int i : points) {
        tree.insert(i);
    }

    REQUIRE(tree.root != nullptr);
    if (tree.root != nullptr) {
        REQUIRE(tree.getHeight() == 3);
        REQUIRE(checkRedBlackProperty(tree.root));
    }

    for (int i : points) {
        REQUIRE(tree.contains(i));
    }
}
