#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>

struct Node
{
    Node * parent;
    Node * left;
    Node * right;

    unsigned int time;
    std::string program;
    int length;
};

#endif
