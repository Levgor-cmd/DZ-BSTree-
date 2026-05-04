#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace __BSTree__ {

    class BSTree
    {
        struct Node
        {
            unsigned int key;
            Node* right = nullptr;
            Node* left = nullptr;
            Node(unsigned int val) : key(val), left(nullptr), right(nullptr) {}
        };

        Node* root = nullptr;

        void clear(Node* node);

        void copyNode(Node* sourceNode, Node*& destNode);

        Node* find(Node* node, unsigned int key);

        Node* findMinNode(Node* node);

        void __remove__(unsigned int key, Node*& node);

        void preOrder(Node* node, std::ostream& os);

        void inOrder(Node* node, std::ostream& os);

        void postOrder(Node* node, std::ostream& os);

        static void printNode(std::ostream& os, Node* node);

        void insertToTree(unsigned int key, Node*& node);

    public:

        BSTree() = default;

        ~BSTree();

        BSTree(const BSTree& source);

        BSTree(BSTree&& source);

        void insert(unsigned int key);

        void remove(unsigned int key);

        void rmTree();

        bool findElement(unsigned int key);

        void preOrderPrint();

        void inOrderPrint();

        void postOrderPrint();

        friend std::ostream& operator<<(std::ostream& os, const BSTree& tree);

        void saveTree(const std::string& filename);

        void readTree(const std::string& filename);
    };
}
