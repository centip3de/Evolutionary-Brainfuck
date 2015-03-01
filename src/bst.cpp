
#include "bst.hpp"

BinaryTree::BinaryTree()
{
    root = NULL;
}

BinaryTree::BinaryTree(Node * node)
{
    root = node;
}

BinaryTree::~BinaryTree()
{
}

Node * BinaryTree::search(unsigned int time)
{
    return search(time, root);
}

Node * BinaryTree::search(unsigned int time, Node * node)
{
    if(node != NULL)
    {
        if(time == node->time)
        {
            return node;
        }
        else if(time < node->time)
        {
            search(time, node->left);
        }
        else
        {
            search(time, node->right);
        }
   }
   return NULL;
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

bool BinaryTree::remove(Node * node)
{
    return true;
}
