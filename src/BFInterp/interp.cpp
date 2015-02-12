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
    return brace_map[pos];
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
    int callStack[300];
    int callIndex = 0;

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
                callStack[callIndex] = pos;
                callIndex++;
            }
            else
            {
                pos = endBrace();
            }
        }
        else if(token == ']')
        {
            pos = callStack[callIndex] - 1;
        }
        else
        {
            continue;
        }

        pos++;
    }
}

int main()
{
    string fileName;
    string line;
    string text;

    cout << "Insert a filename to run: ";
    cin >> fileName; 

    ifstream file(fileName);

    if(file.is_open())
    {
        while(getline(file, line))
        {
            text += line;
        }
        file.close();

        cout << "File contents read, beginning interpretation:" << endl << endl;

        /* Segfaults for now. 
        Interp interp(text);
        interp.execute();
        */ 
    }
    else
    {
        cout << "Error: Unable to open file, " << fileName << endl;
        exit(1);
    }

    return 0;
}
