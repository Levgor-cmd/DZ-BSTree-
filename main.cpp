#include <iostream>
#include "BSTree.hpp"

using namespace __BSTree__;

int main() {
    BSTree tree;

    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);

    std::cout << "Original tree:" << std::endl;
    std::cout << tree << std::endl;

    std::cout << "Pre-order: " << std::endl;
    tree.preOrderPrint();

    std::cout << "In order: " << std::endl;
    tree.inOrderPrint();

    std::cout << "Post-order: " << std::endl;
    tree.postOrderPrint();

    std::cout << "Search 6:" << ( tree.findElement(6) ? "found" : "not found" ) << std::endl;

    std::cout << "Search 20:" << ( tree.findElement(20) ? "found" : "not found" ) << std::endl;

    tree.remove(3);

    std::cout << "Tree after 3 was removed: " << std::endl;
    std::cout << tree << std::endl;

    tree.saveTree("file.txt");
    std::cout << "Tree saved" << std::endl;

    BSTree treeCopied(tree);

    std::cout << "Copy of tree:" << std::endl;
    std::cout << treeCopied << std::endl;

    BSTree treeMoved(std::move(tree));

    tree.readTree("file.txt");

    std::cout << "Tree after reading from file: " << std::endl;
    std::cout << tree << std::endl;

    tree.rmTree();
    treeCopied.rmTree();
    treeMoved.rmTree();

    std::cout << "tree:" << std::endl;
    std::cout << tree << std::endl;

    std::cout << "treeCopied:" << std::endl;
    std::cout << treeCopied << std::endl;

    std::cout << "treeMoved:" << std::endl;
    std::cout << treeMoved << std::endl;

    return 0;
}
