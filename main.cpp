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

        void clear(Node* node)
        {
            if (node == nullptr)
            {
                return;
            }
            clear(node->right);
            clear(node->left);
            delete node;
        }
        void copyNode(Node* sourceNode, Node*& destNode)
        {
            if (sourceNode == nullptr)
            {
                return;
            }
            destNode = new Node(sourceNode->key);
            copyNode(sourceNode->right, destNode->right);
            copyNode(sourceNode->left, destNode->left);
        }

        Node* find(Node* node, unsigned int key)
        {
            if (node == nullptr)
            {
                return nullptr;
            }
            if (node->key == key)
            {
                return node;
            }
            if (key < node->key)
            {
                return find(node->left, key);
            }
            if (key > node->key)
            {
                return find(node->right, key);
            }
        }

        Node* findMinNode(Node* node)
        {
            if (node->left == nullptr)
            {
                return node;
            }
            return findMinNode(node->left);
        }

        void __remove__(unsigned int key, Node*& node)
        {
            if (node == nullptr)
            {
                return;
            }
            else if (key < node->key)
            {
                __remove__(key, node->left);
            }
            else if (key > node->key)
            {
                __remove__(key, node->right);
            }
            else
            {
                if (node->left == nullptr)
                {
                    auto temp = node->right;
                    delete node;
                    node = temp;
                }
                else if (node->right == nullptr)
                {
                    auto temp = node->left;
                    delete node;
                    node = temp;
                }
                else
                {
                    Node* minNode = findMinNode(node->right);
                    node->key = minNode->key;
                    __remove__(minNode->key, node->right);
                }
            }
        }

        void preOrder(Node* node, std::ostream& os)
        {

            if (node == nullptr)
            {
                return;
            }
            os << node->key << std::endl;
            preOrder(node->left, os);
            preOrder(node->right, os);
        }

        void inOrder(Node* node, std::ostream& os)
        {
            if (node == nullptr)
            {
                return;
            }
            inOrder(node->left, os);
            os << node->key << std::endl;
            inOrder(node->right, os);
        }

        void postOrder(Node* node, std::ostream& os)
        {
            if (node == nullptr)
            {
                return;
            }
            postOrder(node->left, os);
            postOrder(node->right, os);
            os << node->key << std::endl;
        }

        static void printNode(std::ostream& os, Node* node)
        {
            if (node == nullptr)
            {
                return;
            }
            printNode(os, node->left);
            os << node->key << std::endl;
            printNode(os, node->right);
        }

        void insertToTree(unsigned int key, Node*& node)
        {
            if (node == nullptr)
            {
                node = new Node(key);
                return;
            }
            if (key < node->key)
            {
                insertToTree(key, node->left);
            }
            else if (key > node->key)
            {
                insertToTree(key, node->right);
            }
            else
            {
                return;
            }
        }

    public:

        BSTree() = default;

        ~BSTree()
        {
            clear(root);
        }

        BSTree(const BSTree& source)
        {
            root = nullptr;
            copyNode(source.root, root);
        }

        BSTree(BSTree&& source)
        {
            this->root = source.root;
            source.root = nullptr;
        }

        void insert(unsigned int key)
        {
            insertToTree(key, root);
        }

        void remove(unsigned int key)
        {
            __remove__(key, root);
        }

        void rmTree()
        {
            clear(root);
            root = nullptr;
        }

        bool findElement(unsigned int key)
        {
            if (find(root, key) )
            {
                return true;
            }
            return false;
        }

        void preOrderPrint()
        {
            preOrder(root, std::cout);
        }

        void inOrderPrint()
        {
            inOrder(root, std::cout);
        }

        void postOrderPrint()
        {
            postOrder(root, std::cout);
        }

        friend std::ostream& operator<<(std::ostream& os, const BSTree& tree);

        void saveTree(const std::string& filename)
        {
            std::ofstream file(filename);
            if (!file.is_open())
            {
                std::cerr << "Unable to open file " << filename << std::endl;
                return;
            }
            inOrder(root, file);
            file.close();
        }

        void readTree(const std::string& filename)
        {
            std::ifstream file(filename);
            if (!file.is_open())
            {
                std::cerr << "Unable to open file " << filename << std::endl;
                return;
            }
            std::string line;
            while (std::getline(file, line))
            {
                try
                {
                    unsigned int key = stoi(line);
                    insertToTree(key, root);
                }
                catch (std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    return;
                }
            }
            file.close();
        }
    };

    std::ostream& operator<<(std::ostream& os, const BSTree& tree)
    {
        BSTree::printNode(os, tree.root);
        return os;
    }
}

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

