#ifndef INTERP_HPP_
#define INTERP_HPP_

#include <string>

using namespace std;

class Interp
{
    public:
        Interp(string text);
        ~Interp();
        char getToken();
        bool atEnd();
        bool testWhile();
        int endBrace();
        void execute();

    private:
        string text;
        int pos;
        char * ptr;
        char array[30000];
        char brace_map[300];

};
#endif
