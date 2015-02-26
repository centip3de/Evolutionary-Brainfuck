#ifndef INTERP_HPP_
#define INTERP_HPP_

#include <string>
#include <map>
#include <stack>

using namespace std;

/* I don't feel like typing map<int, int> and stack<int> a lot. */
typedef map<int, int>Map;
typedef stack<int>Stack;

class Interp
{
    /* The interpreter class. Contains everything needed to interpret a Brainfuck file. */
    public:
        Interp(string text);
        ~Interp();
        char getToken();
        bool atEnd();
        bool testWhile();
        int endBrace();
        void execute();
        void buildBraceMap();

    private:
        string text;
        int pos;
        char * ptr;
        char array[30000];
        Map braceMap;

};
#endif
