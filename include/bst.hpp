#ifndef BST_HPP_
#define BST_HPP_

#include "node.hpp"

class BinaryTree
{
    public:
        BinaryTree();
        BinaryTree(Node * node);
        ~BinaryTree();

        Node * search(unsigned int time, int length);
        Node * search(unsigned int time, int length, Node * node);

        bool insert(unsigned int time, int length);
        bool insert(Node * root, unsigned int time, int length);

    private:
        Node * root;
};

#endif

