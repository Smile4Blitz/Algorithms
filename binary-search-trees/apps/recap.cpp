#include <fstream>
#include <iostream>

#include "tree.hpp"

int main()
{
    Tree<int> tree;

    tree.add(9);
    tree.add(5);
    tree.add(14);
    tree.add(2);
    tree.add(7);
    tree.add(11);
    tree.add(16);

    std::ofstream full_tree("full_tree.dot");
    full_tree << tree;

    tree.remove(14);

    std::ofstream after_deletion("after_deletion.dot");
    after_deletion << tree;

    const auto printer = [](const Node<int> *node)
    { std::cout << node->key << " "; };

    std::cout << "in order = ";
    tree.traverse<inorder>(printer);
    std::cout << std::endl;

    std::cout << "pre order = ";
    tree.traverse<preorder>(printer);
    std::cout << std::endl;

    std::cout << "post order = ";
    tree.traverse<postorder>(printer);
    std::cout << std::endl;

    Node<int> *node = tree.find(2);
    if (node != nullptr)
    {
        std::cout << "Found node for key: " << node->key << std::endl;
    }

    Node<int> *not_found = tree.find(21);
    if (not_found == nullptr)
    {
        std::cout << "No node for key: " << 21 << std::endl;
    }

    int total = 0;
    tree.traverse<inorder>([&total](const Node<int> *node)
                           { total += node->key; });

    std::cout << "sum = " << total << std::endl;

    int low = 4;
    int high = 14;
    std::cout << "range(" << low << ", " << high << ") = [ ";

    for (auto val : tree.range(low, high))
    {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;

    return 0;
}
