#ifndef BST_HPP_
#define BST_HPP_

#include "node.hpp"

class BinaryTree
{
    public:
        BinaryTree();
        BinaryTree(Node * node);
        ~BinaryTree();
        Node * search(unsigned int time);
        Node * search(unsigned int time, Node * node);
        bool insert(Node * root, Node * node);
        bool remove(Node * node);

    private:
        Node * root;
};

#endif

