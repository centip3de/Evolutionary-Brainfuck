#ifndef NODE_HPP_
#define NODE_HPP_

class Node
{
    public:
        /* Constructors/destructors */
        Node(unsigned int time, int length, std::string program, Node parent);
        ~Node();

    private:
        Node * parent;
        Node * left;
        Node * right;

        unsigned int time;
        std::string program;
        int length;
};

#endif
