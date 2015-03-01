
#include "bst.hpp"

BinaryTree::BinaryTree(Node node)
{
    root = node;
}

BinaryTree::~BinaryTree()
{
}

Node BinaryTree::search(Node node)
{
    // Placeholder
    return node;
}

bool BinaryTree::insert(Node * root, Node * node)
{
    if(root->parent == NULL)
    {
        root = node;
        return true;
    }
    else
    {
        if(node->time < root->time)
        {
            if(root->left == NULL)
            {
                root->left = node;
                return true;
            }
            else
            {
                insert(root->left, node);
            }
        }
        else if(node->time > root->time)
        {
            if(root->right == NULL)
            {
                root->right = node;
                return true;
            }
            else
            {
                insert(root->right, node);
            }
        }
   }

   return false;
}

bool BinaryTree::remove(Node node)
{
    // Placeholder
    return true;
}
