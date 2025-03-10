#ifdef _MSC_VER
#include <crtdbg.h>
#else
#define _ASSERT(expr) ((void)0)

#define _ASSERTE(expr) ((void)0)
#endif
#include <iostream>
#include <memory>
#include <vector>

#include "tree.h"

int main() {
    LeftLeaningRedBlackTree tree;

    tree.insert(10);
    tree.insert(18);
    tree.insert(7);
    tree.insert(15);
    tree.insert(16);
    tree.insert(30);
    tree.insert(25);
    tree.insert(40);
    tree.insert(60);

    tree.deleteMin();
    tree.deleteMin();
    tree.deleteMin();

    tree.drawTree();
    tree.drawDotTree("tree.dot");

    return 0;
}