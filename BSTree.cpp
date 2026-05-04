#include "BSTree.hpp"

namespace __BSTree__
{

    void BSTree::clear(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear(node->right);
        clear(node->left);
        delete node;
    }

    void BSTree::copyNode(Node* sourceNode, Node*& destNode)
    {
        if (sourceNode == nullptr)
        {
            return;
        }
        destNode = new Node(sourceNode->key);
        copyNode(sourceNode->right, destNode->right);
        copyNode(sourceNode->left, destNode->left);
    }

    BSTree::Node* BSTree::find(Node* node, unsigned int key)
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
        return nullptr;
    }

    BSTree::Node* BSTree::findMinNode(Node* node)
    {
        if (node->left == nullptr)
        {
            return node;
        }
        return findMinNode(node->left);
    }

    void BSTree::__remove__(unsigned int key, Node*& node)
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

    void BSTree::preOrder(Node* node, std::ostream& os)
    {
        if (node == nullptr)
        {
            return;
        }
        os << node->key << std::endl;
        preOrder(node->left, os);
        preOrder(node->right, os);
    }

    void BSTree::inOrder(Node* node, std::ostream& os)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrder(node->left, os);
        os << node->key << std::endl;
        inOrder(node->right, os);
    }

    void BSTree::postOrder(Node* node, std::ostream& os)
    {
        if (node == nullptr)
        {
            return;
        }
        postOrder(node->left, os);
        postOrder(node->right, os);
        os << node->key << std::endl;
    }

    void BSTree::printNode(std::ostream& os, Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        printNode(os, node->left);
        os << node->key << std::endl;
        printNode(os, node->right);
    }

    void BSTree::insertToTree(unsigned int key, Node*& node)
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

    BSTree::~BSTree()
    {
        clear(root);
    }

    BSTree::BSTree(const BSTree& source)
    {
        root = nullptr;
        copyNode(source.root, root);
    }

    BSTree::BSTree(BSTree&& source)
    {
        this->root = source.root;
        source.root = nullptr;
    }

    void BSTree::insert(unsigned int key)
    {
        insertToTree(key, root);
    }

    void BSTree::remove(unsigned int key)
    {
        __remove__(key, root);
    }

    void BSTree::rmTree()
    {
        clear(root);
        root = nullptr;
    }

    bool BSTree::findElement(unsigned int key)
    {
        if (find(root, key))
        {
            return true;
        }
        return false;
    }

    void BSTree::preOrderPrint()
    {
        preOrder(root, std::cout);
    }

    void BSTree::inOrderPrint()
    {
        inOrder(root, std::cout);
    }

    void BSTree::postOrderPrint()
    {
        postOrder(root, std::cout);
    }

    void BSTree::saveTree(const std::string& filename)
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

    void BSTree::readTree(const std::string& filename)
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
                unsigned int key = std::stoi(line);
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

    std::ostream& operator<<(std::ostream& os, const BSTree& tree)
    {
        BSTree::printNode(os, tree.root);
        return os;
    }

}
