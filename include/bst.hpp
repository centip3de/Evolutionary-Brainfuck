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

        bool insert(unsigned int time);
        bool insert(Node * root, unsigned int time);

    private:
        Node * root;
};

#endif

