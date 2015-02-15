#include <iostream>
#include <string>
#include <cstring> /* For memset */
#include <fstream>

#include "interp.hpp"

using namespace std;

Interp::Interp(string text)
{
    /*  Constructor for the Interp class. Initializes the variables, and builds the brace map. 
        Args:
            string text - The string of characters to interpret
        Returns:
            A new object of this type.
    */

    this->text = text;
    pos = 0;
    ptr = array;
    memset(array, 0, 30000);
    buildBraceMap();
}

Interp::~Interp()
{
    /*  Destructor for the Interp class. Literally does nothing.
        Args:
            None
        Returns:
            None
    */
}

bool Interp::atEnd()
{
    /*  Tests if the interpreter is at the end of the string.
        Args:
            None
        Returns:
            True if at the end, False if not at the end.
    */

    return text.length() == pos;
}

int Interp::endBrace()
{
    /*  Gets the ending brace (right brace in a left/right pair) for the brace at the current position. 
        Args:
            None
        Returns:
            The right brace match to the current brace at pos, or -1 if no brace match could be found.
    */

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
    /*  Builds a hash map for the braces, with the key being the left braces position, and the value being 
        the matching right braces position. This information is stored in the public variable, "braceMap".
        Args:
            None
        Returns:
            None
   */
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
    /*  Checks if the current pointer is pointing to a 0 value, useful for testing if loops should be taken.
        Args:
            None
        Returns:
            True if the value the pointer is pointing to is 0, false otherwise.
    */

    return (*ptr) != 0;
}

char Interp::getToken()
{
    /*  Gets the token at the current position in the text.
        Args:
            None
        Returns:
            The token at the current position in the string.
    */

    return text[pos];
}

void Interp::execute()
{
    /*  Executes the current text given to it.
        Args:
            None
        Returns:
            None
    */

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
    /*  The entry point for the program. Takes a filename as the argument, and then attempts to interpret the given file.
        Args:
            int argc            = The amount of command-line arguments
            const char * argv[] = The command-line arguments
        Returns:
            None
    */

    string fileName;
    string line;
    string text;

    /* Sets the filename to the one passed in through the command-line */ 
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
        /* Reads the file, line-by-line. */
        while(getline(file, line))
        {
            text += line;
        }
        file.close();

        cout << "File contents read, beginning interpretation:" << endl << endl;

        /* Attempts to interpret the file. */
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
