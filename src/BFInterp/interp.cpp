#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "interp.hpp"

using namespace std;

Interp::Interp(string text)
{
    this->text = text;
    pos = 0;
    ptr = array;
    memset(array, 0, 30000);
    buildBraceMap();
}

Interp::~Interp()
{
}

bool Interp::atEnd()
{
    return text.length() == pos;
}

int Interp::endBrace()
{

    Map::iterator brace = braceMap.find(pos);
    if(brace != braceMap.end())
    {
        int second = brace->second;
        cout << "Returning " << second << " for brace at " << pos << endl;
        return second;
    }
    else
    {
        return -1;
    }
}

void Interp::buildBraceMap()
{
    Stack lbrace_stack;

    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] == '[')
        {
            lbrace_stack.push(i);
        }
        else if(text[i] == ']')
        {
            int lbrace = lbrace_stack.top();
            lbrace_stack.pop();
            
            cout << "Attaching brace at, " << lbrace << " to brace at " << i << endl;
            braceMap.insert(pair<int, int>(lbrace, i));
        }
    }
}

bool Interp::testWhile()
{
    return (*ptr) != 0;
}

char Interp::getToken()
{
    return text[pos];
}

void Interp::execute()
{
    Stack callStack;

    while(!atEnd())
    {
        char token = getToken();

        if(token == '>')
        {
            ++ptr;
        }
        else if(token == '<')
        {
            --ptr;
        }
        else if(token == '+')
        {
            *ptr = (*ptr + 1)%256;
        }
        else if(token == '-')
        {
            *ptr = (*ptr - 1)%256;
        }
        else if(token == '.')
        {
            putchar(*ptr);
        }
        else if(token == ',')
        {
            (*ptr) = getchar();
        }
        else if(token == '[')
        {
            if(testWhile())
            {
                callStack.push(pos);
            }
            else
            {
                pos = endBrace();
            }
        }
        else if(token == ']')
        {
            int prev = callStack.top() - 1;
            callStack.pop();
            pos = prev;
        }
        else
        {
            continue;
        }

        pos++;
    }
}

int main(int argc, const char * argv[])
{
    string fileName;
    string line;
    string text;

    if(argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        cerr << "Error: No file provided to interpret." << endl;
        return -1;
    }

    ifstream file(fileName);

    if(file.is_open())
    {
        while(getline(file, line))
        {
            text += line;
        }
        file.close();

        cout << "File contents read, beginning interpretation:" << endl << endl;

        Interp interp(text);
        interp.execute();
    }
    else
    {
        cerr << "Error: Unable to open file, " << fileName << endl;
        return -1;
    }

    return 0;
}
