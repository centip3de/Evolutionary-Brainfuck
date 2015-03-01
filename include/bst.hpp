#ifndef BST_HPP_
#define BST_HPP_

#include "node.hpp"

class BinaryTree
{
    public:
        BinaryTree(Node node);
        ~BinaryTree();
        Node search(Node node);
        bool insert(Node * root, Node * node);
        bool remove(Node node);

    private:
        Node root;
};

#endif

