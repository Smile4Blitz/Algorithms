#ifdef _MSC_VER
#include <crtdbg.h>
#else
#define _ASSERT(expr) ((void)0)

#define _ASSERTE(expr) ((void)0)
#endif
#include <iostream>
#include <memory>
#include <vector>

#include "redBlackTree.h"

int main() {
    RedBlackTree tree;

    // std::vector<int>* list_of_inserted_keys = new std::vector<int>;
    // for (int i = 0; i < 20; i++) {
    //     while (true) {
    //         int new_key = rand() % 1000 + 1;
    //         if (std::find(list_of_inserted_keys->begin(), list_of_inserted_keys->end(), new_key) == list_of_inserted_keys->end()) {
    //             list_of_inserted_keys->push_back(new_key);
    //             tree.insert(new_key);
    //             break;
    //         }
    //     }
    // }

    std::cout << "Inserting keys into the Red-Black Tree" << std::endl;

    tree.insert(4);
    tree.insert(7);
    tree.insert(12);
    tree.insert(15);
    tree.insert(3);
    tree.insert(5);
    tree.insert(14);
    tree.insert(18);
    tree.insert(16);
    tree.insert(17);
    tree.insert(99);
    tree.insert(100);
    tree.insert(111);
    tree.insert(112);

    std::cout << "height: " << tree.getHeight() << std::endl;

    // tree.drawTree();
    tree.drawDotTree("tree.dot");

    // tree.deleteNode(18);

    // tree.drawTree();
    tree.drawDotTree("tree_delete.dot");

    std::cout << "In-order traversal of the Red-Black Tree: ";
    tree.inOrderTraversal();

    std::cout << "Searching for key 12: ";
    if (tree.contains(12))
        std::cout << "Found\n";
    else
        std::cout << "Not Found\n";

    std::cout << "Searching for key 11: ";
    if (tree.contains(11))
        std::cout << "Found\n";
    else
        std::cout << "Not Found\n";

    return 0;
}
