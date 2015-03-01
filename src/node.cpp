#include <string>
#include "node.hpp"

using namespace std;

/* Constructor/destructors */
Node::Node(unsigned int time, int length, string program, Node parent)
{
    this->time = time; 
    this->length = length;
    this->program = program;
    this->parent = &parent;
}

Node::~Node()
{
}
