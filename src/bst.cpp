#include "bst.hpp"

BinaryTree::BinaryTree()
{
    /*  Default constructor. Sets the root node to NULL.

        Args:
            None

        Returns:
            BinaryTree object with root node equal to NULL.
    */

    root = NULL;
}

BinaryTree::BinaryTree(Node * node)
{
    /*  Constructor that takes a node to set to the root.

        Args:
            Node * node - The node to set to root

        Returns:
            BinaryTree object with root equal to the passed in node.
    */

    root = node;
}

BinaryTree::~BinaryTree()
{
    /*  Default destructor. No memory is allocated, so no memory needs to be freed. 

        Args:
            None

        Returns:
            None
    */
}

Node * BinaryTree::search(unsigned int time)
{
    /*  Overloaded version of search function. Calls the normal
        search function starting at the root node.

        Args:
            unsigned int time - The time to search for

        Returns:
            A pointer to the node if it was found, NULL if it wasn't.
    */

    return search(time, root);
}

Node * BinaryTree::search(unsigned int time, Node * node)
{
    /*  Searches the binary tree for the given time, starting at the 
        given node.

        Args:
            unsigned int time   - The time to search for
            Node * node         - The node to start at

        Returns:
            A pointer to the node if it was found, NULL if it wasn't.
    */

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

bool BinaryTree::insert(Node * node)
{
    /*  Overloaded version of the insert function, that starts the 
        insertion at the root node.

        Args:
            Node * node - The node to insert

        Returns:
            True if the insertion was successful, false if it wasn't.
    */

    return insert(root, node);
}

bool BinaryTree::insert(Node * root, Node * node)
{
    /*  Inserts the given node into the tree, starting at the passed in 'root'.
        
        Args:
            Node * root - The place to insert under
            Node * node - The node to insert

        Returns:
            True if the insertion was successful, false if it wasn't
    */

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

